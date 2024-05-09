int botao_v = 9;
int botao_a = 10;
unsigned long tempoAnterior = 0; // Variável para armazenar o tempo anterior
const long intervalo = 1000; // Intervalo de 1 segundo
int segundos = 0; // Variável para contar os segundos
int minutos = 0; // Variável para contar os minutos
bool botaoPressionado = false; // Variável para indicar se o botão foi pressionado
unsigned long tempoInicio = 0; // Variável para armazenar o tempo de início

#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

void setup() {
  pinMode(botao_v, INPUT_PULLUP);
  pinMode(botao_a, INPUT_PULLUP);
  lcd.begin(16,2);
}

// Função de contar o tempo
void timer() {
  lcd.clear(); // Limpa o LCD
  while(true){ // Loop infinito
    if(digitalRead(botao_v) == LOW){ // Se o botão vermelho for pressionado
      while(digitalRead(botao_a) == HIGH){ // Enquanto o botão azul não for pressionado
        lcd.setCursor(0,1); // Define a posição do cursor do LCD
        lcd.print("Azul = Continuar"); // Exibe uma mensagem no LCD

        if(digitalRead(botao_v) == LOW){ // Se o botão vermelho for pressionado novamente
          while (digitalRead(botao_a) == HIGH){ // Enquanto o botão azul não for pressionado
            if (digitalRead(botao_v) == LOW && !botaoPressionado){ // Se o botão vermelho for pressionado e o botão não estiver sido previamente pressionado
              tempoInicio = millis(); // Armazena o tempo atual
              botaoPressionado = true; // Marca o botão como pressionado
            }

            if (digitalRead(botao_v) == HIGH && botaoPressionado){ // Se o botão vermelho for solto e o botão estiver pressionado
              unsigned long tempoPressionado = millis() - tempoInicio; // Calcula o tempo de pressionamento do botão
              botaoPressionado = false; // Marca o botão como não pressionado
              if (tempoPressionado >= 3000){ // Se o botão foi pressionado por mais de 3 segundos
                return; // Sai da função
              }
            }
          }
        }
      }
      lcd.clear(); // Limpa o LCD
    }

    unsigned long temporizador = millis(); // Obtém o tempo atual em milissegundos

    if (temporizador - tempoAnterior >= intervalo){ // Se passou o intervalo de 1 segundo
      tempoAnterior = temporizador; // Atualiza o tempo anterior

      // Incrementa os segundos e os minutos conforme necessário
      segundos++;
      if (segundos >= 60){
        segundos = 0;
        minutos++;
      }

      // Exibe o tempo no LCD
      lcd.setCursor(1,0);
      lcd.print("Tempo: ");
      if (minutos < 10) lcd.print("0");
      lcd.print(minutos);
      lcd.print(":");
      if (segundos < 10) lcd.print("0");
      lcd.print(segundos);
      lcd.setCursor(0,1);
      lcd.print("Vermelho = Pause");
    }
  }
}

void loop() {
  lcd.clear(); // Limpa o LCD
  segundos = 0; // Reinicia os segundos
  minutos = 0; // Reinicia os minutos
  if(digitalRead(botao_a) == LOW){ // Se o botão azul for pressionado
    timer(); // Chama a função timer
  } else {
    lcd.setCursor(3,0);
    lcd.print("Botao Azul=");
    lcd.setCursor(5,1);
    lcd.print("START");
  }

  delay(500); // Aguarda 500 milissegundos
}
