#include <Wire.h>                 // Librería para la comunicación I2C

///////////////////////////////////////////// PID /////////////////////////////////////////////////

float Kp = 20.0;                                            // Ganancia proporcional (Ajustar este valor)
float Ki = 0.0;                                             // Ganancia integral (Ajustar este valor)
float Kd = 0.0;                                             // Ganancia derivativa (Ajustar este valor)

float V_deseado = 0.0;                                      // Ángulo objetivo para mantener el equilibrio (Set point)
float V_medido;                                             // Entrada del PID (ángulo Roll)

float e_a; float e_p = 0.0;                                 // Variables del error actual y el error pasado [e(t)]
double delta_t_s = 0.0; double delta_t_ms;                  // Variables para el ΔT el cual tengo dos versiones, una para ms y otra de segundos que es la que usare.
float e_i_a; float e_i_p = 0.0;                             // Varibles de los errores integral actual y pasado [∫e(t) dt]
float e_d ;                                                 // Variable para el error derivativo [e(t)']
double Tiempo_pasado_pid = 0.0; double Tiempo_actual_pid;   // Variables para obtener el ΔT.
float PID;                                                  // La salida del PID general.

/////////////////////////////////////////// MPU 6050 ////////////////////////////////////////////

const int MPU6050_ADDR = 0x68;                            // Dirección I2C del MPU6050
const int GYRO_XOUT_H = 0x43;                             // Registro del giroscopio X del mpu6050
const int PWR_MGMT_1 = 0x6B;                              // Registro del modo suspendion del mpu6050
const int CONFIG = 0x1A;                                  // Registro para configurar el filtro del mpu6050
const int GYRO_CONFIG = 0x1B;                             // Registro para configurar la sensibilidad del mpu6050

unsigned long Tiempo_actual;                              // Variable para almacenar el tiempo de la última lectura
const int numero_de_lecturas = 200;                       // Defino el número de lecturas que se tomarán para la calibración del giroscopio
float gyroXoffset = 0.0, gyroYoffset = 0.0, gyroZoffset = 0.0;  // Defino variables para almacenar los offsets del giroscopio después de la calibración

float RateRoll,RatePitch,RateYaw;                         // Defino variables para almacenar las tasas de rotación (Rate [°/s]) en los ejes de Roll, Pitch y Yaw  

float AngleRoll, AnglePitch, AngleYaw;                    // Defino variables para almacenar los angulos de rotación (Angle [°]) en los ejes de Roll, Pitch y Yaw

/////////////////////////////////////// Driver A4988 ////////////////////////////////////////////

const int DIR_L = 32;             // Pin para la dirección del motor izquierdo
const int STEP_L = 33;            // Pin para los pasos del motor izquierdo
const int DIR_R = 25;             // Pin para la dirección del motor derecho
const int STEP_R = 26;            // Pin para los pasos del motor derecho

const int MS1 = 27;               // Pin para configurar los micropasos
const int MS2 = 14;               // Pin para configurar los micropasos
const int MS3 = 12;               // Pin para configurar los micropasos

//////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  Serial.begin(115200);           // Configuro la velocidad de comunicación serial a 115200 baudios para la depuración
  Wire.setClock(400000);          // Configuro la velocidad del reloj I2C a 400kHz para una comunicación más rápida con el MPU6050
  Wire.begin();                   // Inicio la comunicación I2C
  delay(250);                     // Introduzco un pequeño retraso para permitir que todo se estabilice

  pinMode(DIR_L, OUTPUT);         // Configuro el pin de DIR_L como salida
  pinMode(STEP_L, OUTPUT);        // Configuro el pin de STEP_L como salida
  pinMode(DIR_R, OUTPUT);         // Configuro el pin de DIR_R como salida
  pinMode(STEP_R, OUTPUT);        // Configuro el pin de STEP_R como salida
  pinMode(MS1, OUTPUT);           // Configuro el pin de MS1 como salida
  pinMode(MS2, OUTPUT);           // Configuro el pin de MS2 como salida
  pinMode(MS3, OUTPUT);           // Configuro el pin de MS3 como salida

  digitalWrite(MS1,LOW);           // Seteo la configuracion de micropasos del A4988 para los nema 17.
  digitalWrite(MS2, LOW);           // Seteo la configuracion de micropasos del A4988 para los nema 17.
  digitalWrite(MS3,LOW);            // Seteo la configuracion de micropasos del A4988 para los nema 17.
  
  Wire.beginTransmission(MPU6050_ADDR);                                   // Comienzo una transmisión I2C al MPU6050 en la dirección 0x68 (La que viene por defecto)
  Wire.write(PWR_MGMT_1);                                                 // Escribo en el registro 0x6B del MPU6050 para despertarlo del modo de suspensión
  Wire.write(0x00);                                                       // Escribo 0x00 en el registro 0x6B para poner el MPU6050 en modo activo
  Wire.endTransmission();                                                 // Termino la transmisión I2C

  Calibracion_del_giroscopio();                                            // Llamo a la función para calibrar el giroscopio
  Tiempo_actual  = millis();                                               // Inicializo la variable con el tiempo actual en milisegundos desde que comenzó el programa
}

void loop() {
  gyro_signal();                                                          // Llamo a la función que lee los datos del giroscopio y actualiza las tasas de rotación
  Calcular_angulos_reales();                                              // Llamo a la función que calcula e imprime los ángulos reales de Roll, Pitch y Yaw
  controlPID();                                                           // Llama al controlador PID 
  //delay(20);                                                              // Introduzco un retraso de 50ms para reducir la frecuencia de actualización del bucle principal
}

///////////////////////////////// FUNCIONES PROPIAS ////////////////////////////////////////////


void Calibracion_del_giroscopio() {
  long sumX = 0, sumY = 0, sumZ = 0;                                        // Inicializo sumas para cada eje a 0, que se utilizarán para calcular los offsets

  //Serial.println("Deje el MPU6050 quieto para poder calibrarlo.");          // Imprimo un mensaje indicando que se está realizando la calibración
  //delay(2000);                                                              // Tiempo para estabilizar

  for (int i = 0; i < numero_de_lecturas; i++) {                            // Realizo un bucle para tomar varias lecturas y calcular la media de los valores del giroscopio

    Wire.beginTransmission(MPU6050_ADDR);                                   // Comienzo una transmisión I2C al MPU6050 en la dirección 0x68
    Wire.write(GYRO_XOUT_H);                                                // Escribo en el registro 0x43 para solicitar los datos del giroscopio
    Wire.endTransmission();                                                 // Termino la transmisión I2C
    Wire.requestFrom(MPU6050_ADDR, 6);                                      // Solicito 6 bytes de datos del giroscopio (2 bytes por eje: X, Y, Z)

    int16_t GyroX = Wire.read() << 8 | Wire.read();                         // Leo y combino los bytes del valor del eje X del giroscopio
    int16_t GyroY = Wire.read() << 8 | Wire.read();                         // Leo y combino los bytes del valor del eje Y del giroscopio
    int16_t GyroZ = Wire.read() << 8 | Wire.read();                         // Leo y combino los bytes del valor del eje Z del giroscopio

    sumX += GyroX;                                                          // Sumo los valores leídos a las sumas acumuladas para el eje X
    sumY += GyroY;                                                          // Sumo los valores leídos a las sumas acumuladas para el eje Y
    sumZ += GyroZ;                                                          // Sumo los valores leídos a las sumas acumuladas para el eje Z

    delay(10);                                                              // Introduzco un pequeño retraso entre lecturas para asegurar lecturas estables
  }

  gyroXoffset = sumX / numero_de_lecturas;                                  // Calculo el offset del giroscopio con los promedios de las lectura para el eje X
  gyroYoffset = sumY / numero_de_lecturas;                                  // Calculo el offset del giroscopio con los promedios de las lectura para el eje Y
  gyroZoffset = sumZ / numero_de_lecturas;                                  // Calculo el offset del giroscopio con los promedios de las lectura para el eje Z

  //Serial.print("Calibracion completeada.");                                 // Imprimo un mensaje avisando de que la calibracion ya fue completada
  //delay(2000);                                                              // Delay para poder ver este mensaje y que no pase tan rapido.
  //Serial.print(" Gyro X offset: ");
  //Serial.print(gyroXoffset);
  //Serial.print(" Gyro Y offset: ");
  //Serial.print(gyroYoffset);
  //Serial.print(" Gyro Z offset: ");
  //Serial.println(gyroZoffset);
}

void gyro_signal(void){
  Wire.beginTransmission(MPU6050_ADDR);                                     // Comienzo una transmisión I2C al MPU6050 en la dirección 0x68
  Wire.write(CONFIG);                                                       // Escribo en el registro 0x1A para configurar el filtro de paso bajo
  Wire.write(0x05);                                                         // Configuro el filtro de paso bajo en 5 Hz
  Wire.endTransmission();                                                   // Termino la transmisión I2C

  Wire.beginTransmission(MPU6050_ADDR);                                     // Comienzo otra transmisión I2C al MPU6050 en la dirección 0x68
  Wire.write(GYRO_CONFIG);                                                  // Escribo en el registro 0x1B para configurar la sensibilidad del giroscopio
  Wire.write(0x8);                                                          // Configuro la escala completa del giroscopio a ±500 °/s
  Wire.endTransmission();                                                   // Termino la transmisión I2C

  Wire.beginTransmission(MPU6050_ADDR);                                     // Comienzo otra transmisión I2C al MPU6050 en la dirección 0x68
  Wire.write(GYRO_XOUT_H);                                                  // Escribo en el registro 0x43 para solicitar los datos del giroscopio
  Wire.endTransmission();                                                   // Termino la transmisión I2C

  Wire.requestFrom(MPU6050_ADDR,6);                                         // Solicito 6 bytes de datos del giroscopio (2 bytes por eje: X, Y, Z)

  int16_t GyroX=Wire.read()<<8|Wire.read();                                 // Leo y combino los bytes de datos del eje X del giroscopio. 
  int16_t GyroY=Wire.read()<<8|Wire.read();                                 // Leo y combino los bytes de datos del eje Y del giroscopio.
  int16_t GyroZ=Wire.read()<<8|Wire.read();                                 // Leo y combino los bytes de datos del eje Z del giroscopio.

  RateRoll = ((float)GyroX - gyroXoffset) / 65.5;                           // Convierto las lecturas del giroscopio a tasas de rotación en grados por segundo
  RatePitch = ((float)GyroY - gyroYoffset) / 65.5;
  RateYaw = ((float)GyroZ - gyroZoffset) / 65.5;

  //Serial.print("Roll rate[°/s]= ");                                       // Prints opcionales de las tasas de rotacion del giroscopio.
  //Serial.print(RateRoll);
  //Serial.print(" | Pitch rate[°/s]= ");
  //Serial.print(RatePitch);
  //Serial.print(" | Yaw rate[°/s]= ");
  //Serial.println(RateYaw);
  
  }

  void Calcular_angulos_reales(){
  unsigned long currentTime = millis();                                   // Obtengo el tiempo actual en milisegundos
  float deltaTime = (currentTime - Tiempo_actual) / 1000.0;               // Calculo el tiempo transcurrido desde la última lectura en segundos
  Tiempo_actual = currentTime;                                            // Actualizo lastTime con el tiempo actual

  AngleRoll += RateRoll * deltaTime;                                      // Actualizo los ángulos sumando la tasa de rotación multiplicada por el tiempo transcurrido, teniendo el angulo real del eje X.
  AnglePitch += RatePitch * deltaTime;                                    // Actualizo los ángulos sumando la tasa de rotación multiplicada por el tiempo transcurrido, teniendo el angulo real del eje Y.
  AngleYaw += RateYaw * deltaTime;                                        // Actualizo los ángulos sumando la tasa de rotación multiplicada por el tiempo transcurrido, teniendo el angulo real del eje Z.
                                                          
  //Serial.print(" | Roll angle[°]= ");                                   // Imprimo los ángulos actuales y reales de Roll, Pitch y Yaw en grados 
  //Serial.print(AngleRoll);
  //Serial.print(" | Pitch angle[°]= ");
  //Serial.print(AnglePitch);
  //Serial.print(" | Yaw angle[°]= ");
  //Serial.println(AngleYaw);
  
  }

void controlPID() {
    
    V_medido = AngleRoll;
    e_a = (V_deseado - V_medido);
    Tiempo_actual_pid = millis();
    delta_t_ms = (Tiempo_actual_pid - Tiempo_pasado_pid);
    delta_t_s = delta_t_ms/1000;
    e_d = (e_a - e_p)/(delta_t_s);
    e_i_a = e_i_p + (delta_t_s)*(e_a);
    PID = (Kp*e_a) + (Ki*e_i_a) + (Kd*e_d);
    
     // Actualizacion para el siguiente bucle
  
     Tiempo_pasado_pid = Tiempo_actual_pid;
     e_p = e_a;
     e_i_p = e_i_a;
  
     // Imprimimos valores en el ploter.
  
     //Serial.print(V_deseado);
     //Serial.print(",");
     //Serial.println(V_medido);
  
     Mover_Motores_con_velocidad_variable(PID);
}

void Mover_Motores_con_velocidad_variable(float pid_output) {
  
  int velocidad;             // Variable para la velocidad ajustada por el PID
  int direccion_L, direccion_R;  // Variables para la dirección de los motores

  // Determinar la dirección en función del signo del valor de PID
  if (pid_output > 0) {
    direccion_L = HIGH;  // Dirección hacia adelante para el motor izquierdo
    direccion_R = LOW;   // Dirección hacia atrás para el motor derecho
  } else {
    direccion_L = LOW;   // Dirección hacia atrás para el motor izquierdo
    direccion_R = HIGH;  // Dirección hacia adelante para el motor derecho
  }

  // Determinar la velocidad basada en la magnitud del valor de PID (cuanto más cercano a 0, más lento)
  if (pid_output >=0) {
  velocidad = map(pid_output, 0, 800, 5000, 2000);  // Mapea de 0 a 800
} else if(pid_output <0) {
  // Si pid_output sobrepasa 800, refleja el valor de velocidad
  velocidad = map(pid_output, -800, 0, 2000, 5000);  // Empieza a decrecer
}
velocidad = constrain(velocidad, 2000, 5000);  // Limita el valor entre 1 y 5000

  Serial.println(velocidad);
  
  // Limitar la velocidad máxima y mínima para evitar desbordes

  // Establecer la dirección de los motores
  digitalWrite(DIR_L, direccion_L);
  digitalWrite(DIR_R, direccion_R);

    // Generar los pasos para los motores
  digitalWrite(STEP_L, HIGH);
  digitalWrite(STEP_R, HIGH);
  delayMicroseconds(velocidad);  // Controlar la velocidad del motor
  digitalWrite(STEP_L, LOW);
  digitalWrite(STEP_R, LOW);
  delayMicroseconds(velocidad);

}
