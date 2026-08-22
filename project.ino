#include <RTClib.h>
RTC_DS1307 rtc;

struct Hours {
  int hour;
  int minute;
};
Hours table_hours[] = {
  {7, 15},
  {8, 5},
  {8, 55},
  {9, 15},
  {10, 5},
  {10, 55},
  {11, 45},
  {13, 5},
  {13, 55},
  {14, 45},
  {15, 35},
  //horario teste 
  {17, 32},
  {17, 33}

};
struct Date{
    int day;
    int month;
};
Date holidays[] = {
  {1, 1},   // Confraternização Universal (Nacional)
  {6, 1},   // Dia de Santos Reis (Municipal - Natal)
  {16, 2},  // Carnaval (Ponto Facultativo)
  {17, 2},  // Carnaval (Ponto Facultativo)
  {18, 2},  // Quarta-feira de Cinzas (Ponto Facultativo até 14h, geralmente sem aula)
  {3, 4},   // Sexta-feira Santa (Nacional)
  {21, 4},  // Tiradentes (Nacional)
  {1, 5},   // Dia do Trabalho (Nacional)
  {4, 6},   // Corpus Christi (Ponto Facultativo)
  {7, 9},   // Independência do Brasil (Nacional)
  {3, 10},  // Mártires de Cunhaú e Uruaçu (Estadual - RN)
  {12, 10}, // Nossa Senhora Aparecida (Nacional)
  {15, 10}, // Dia do Professor (Feriado Escolar)
  {28, 10}, // Dia do Servidor Público (Ponto Facultativo)
  {2, 11},  // Finados (Nacional)
  {20, 11}, // Dia da Consciência Negra (Nacional)
  {21, 11}, // Nossa Senhora da Apresentação (Municipal - Natal)
  {24, 12}, // Véspera de Natal (Ponto Facultativo após 13h)
  {25, 12}, // Natal (Nacional)
  {31, 12}  // Véspera de Ano Novo (Ponto Facultativo após 13h)
};

const int SWITCH_PIN = 7;
const int BUZZER = 12;

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("RTC não encontrado!");
    while (1);
  }
  pinMode(BUZZER, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  
};

bool is_system_active(){
  return digitalRead(SWITCH_PIN) == LOW; // low == ativo
};

void alarm(){
  digitalWrite(BUZZER, HIGH);
  delay(8000);
  digitalWrite(BUZZER, LOW);
};

bool validate_hour_and_day(Hours table_hours, DateTime moment){
  
  for (int i = 0; i< sizeof(holidays)/ sizeof(holidays[0]); i++){
    if (
      moment.day() == holidays[i].day &&
      moment.month() == holidays[i].month
    ) {
      return false;
    }
  }
  
  return (
    table_hours.hour == moment.hour() &&
    table_hours.minute == moment.minute() &&
    (moment.dayOfTheWeek() != 5 && moment.dayOfTheWeek() != 0)
  );
};

bool already_alarm = false;
int last_minute = -1;

void loop() {
  DateTime moment = rtc.now();

  if (last_minute != moment.minute()){
    already_alarm = false;
    last_minute = moment.minute();
  }
  if(!is_system_active()){
    return;
  }

  for (int i = 0; i < sizeof(table_hours) / sizeof(table_hours[0]); i++){
    Hours hours = table_hours[i];
    if (validate_hour_and_day(hours, moment)) {
      if (!already_alarm){
        alarm();
        already_alarm = true;
      }
    }
  }
};
