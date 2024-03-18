#include <Wire.h>  // Inclua a biblioteca Wire para comunicação I2C
#include <LiquidCrystal_I2C.h>  // Inclua a biblioteca para o display LCD I2C
#include <DFRobotDFPlayerMini.h> //Inclui a biblioteca DFPLAYER para mp3
#include <tinyexpr.h> //Inclui a biblioteca TINYEXPR para calcular expressões math
#include <math.h>
#include <string.h>
#include <stdio.h>
int error=0; //código de erro para a função da tinyexpr
double res = 0; //Double que irá guardar o resultado
char tecla='h'; //Char que guarda a tecla digitada no momento atual
char str[100]; //Char que guarda string, acho que não está sendo utilizada no código.
String str1=""; //String que guarda toda a equação digitada

DFRobotDFPlayerMini dfplayer; //Define DFPLAYER
LiquidCrystal_I2C lcd(0x27, 16,2); //Define o LCD

byte cols[] = {4, 5, 6, 7}; // Byte com quantidade de colunas da matriz de botões
byte rows[] = {8, 9, 10, 11, 12, 13}; // Byte com quantidade de linhas da matriz de botões
const int rowCount = sizeof(rows) / sizeof(rows[0]); // Calcula a quantidade de elementos no array rows
const int colCount = sizeof(cols) / sizeof(cols[0]); // Calcula a quantidade de elementos no array cols
byte keys[colCount][rowCount];

void setup() {
    lcd.begin(); //Inicia o LCD
    lcd.clear(); //Inicia LCD sem nd mostrando
    lcd.backlight(); //Acende o background do LCD
    Serial.begin(115200); //Define o Serial
    lcd.setCursor(0,0); //Seta cursor na posição 0 e 0 do LCD


//DEFINIÇÃO DE INPUT E INPUT_PULLUP NAS PORTAS DO ARDUINO PARA LINHAS E COLUNAS:


    for (int x = 0; x < rowCount; x++) {
        //Serial.print(rows[x]);
        //Serial.println(" as input");
        pinMode(rows[x], INPUT); //Define a linha[x] (de 0 a 5) como INPUT para receber um sinal na porta digital do arduino
    }

    for (int x = 0; x < colCount; x++) {
        //Serial.print(cols[x]);
        //Serial.println(" as input-pullup");
        pinMode(cols[x], INPUT_PULLUP); //Define a coluna[x] (de 0 a 3) como INPUT_PULLUP para liberar um sinal PULLUP na porta digital do arduino
    }
}
//LEITURA DAS PORTAS DO ARDUINO PARA MAPEAMENTO DO ESTADO DOS BOTÕES

//Basicamente, este código percorre cada coluna do teclado, definindo-a como saída e colocando-a em LOW. 
//Em seguida, ele percorre cada linha do teclado, definindo-as como entrada com pull-up e lendo o estado dos botões.
//Os estados lidos são armazenados na matriz keys.
//Depois de ler todas as linhas para uma coluna específica, a coluna é desativada definindo-a como entrada.
//Este processo é repetido para cada coluna do teclado. Ao final, a matriz keys terá os estados de todos os botões no keypad.
void readMatrix() {
    // Itera sobre as colunas
    for (int colIndex = 0; colIndex < colCount; colIndex++) {
        byte curCol = cols[colIndex]; // Obtém o número do pino da coluna atual
        pinMode(curCol, OUTPUT); //Define o pino da coluna como saída
        digitalWrite(curCol, LOW); // define o pino da coluna como LOW para permitir a leitura das linhas

    // Itera sobre as linhas
        for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
            byte rowCol = rows[rowIndex]; //Obtém o número do pino da linha atual
            pinMode(rowCol, INPUT_PULLUP); //Define o pino da linha como entrada com PULL-UP
            keys[colIndex][rowIndex] = digitalRead(rowCol); //Lê o estado do botão na posição da matriz e armazena em 'keys'
            pinMode(rowCol, INPUT); //Retorna o pino da linha para o modo de entrada padrão
        }
        pinMode(curCol, INPUT); // Desativa a coluna atual definindo-a como entrada
    }
}


void printMatrix() {
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
      // Itera sobre as linhas da matriz
        if (rowIndex < 10)
            Serial.print(F("0")); // Adiciona um zero à esquerda para formatar a saída
        Serial.print(rowIndex); // Imprime o índice da linha
        Serial.print(F(": ")); // Imprime dois pontos após o índice da linha

        for (int colIndex = 0; colIndex < colCount; colIndex++) {
          // Itera sobre as colunas da matriz
            Serial.print(keys[colIndex][rowIndex]); // Imprime o estado do botão na posição [colIndex][rowIndex]
            if (colIndex < colCount - 1)
                Serial.print(F(", ")); // Adiciona uma vírgula e um espaço entre os estados dos botões
        }
        Serial.println(""); // Imprime uma nova linha no final de cada linha da matriz
    } 
    Serial.println(""); // Imprime uma linha em branco adicional para separar as leituras da matriz
    delay(100);
}

void loop() {
    readMatrix(); //MAPEAMENTO DO ESTADO DOS BOTÕES
    //printMatrix(); //PRINTA O ESTADO DOS BOTÕES NO SERIAL PARA VERIFICAR SE ESTÃO FUNCIONANDO
    operador();
}
void cleear(){
char tecla='h';
String str1="";
int count2 = 0;
Serial.println("Clear");
  
}
void opera(){
return;
}
void operador() {
    //Serial.print("\nTo no operador\n");
    int coluna = -1; // Inicializa o contador de coluna
    int linha = -1; // Inicializa o contador de linha
  	int count = 0; // Inicializa o contador para não ter tecla 'h' repetida


    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
       //Itera sobre as linhas da matriz de botões
        linha++; // Incrementa o contador de linha

        //Itera sobre as colunas da matriz de botões
        for (int colIndex = 0; colIndex < colCount; colIndex++) {
            coluna++; //Incrementa o contador de coluna

            //Verifica se o botão na posição atual está pressionado
          	if (keys[colIndex][rowIndex] == HIGH){
          		count++; // Incrementa o contador de botões pressionados
          	}

            //Verifica se o botão na posição atual está solto e se a variável tecla é 'h'
            if (keys[colIndex][rowIndex] == LOW && tecla=='h') {
            	int ValorBotao = (linha * 10) + colIndex; // Calcula o valor do botão com base na posição
                //Serial.print(ValorBotao);
             	
               //Determina a ação a ser tomada com base no valor do botão
                switch (ValorBotao) {
                  	case 0:
                  		tecla='0'; //Define a tecla pressionada como '0'
                      str1+=tecla; //Adiciona '0' à string principal
                      dfplayer.play(3); //Coloca o dfplayer para rodar o audio '0'
                      break;
                  	case 1:
                  		tecla='c';
                      cleear();
                      dfplayer.play(4);
                      break;
                  	case 2:
                  		tecla='r';
                      break;
                  	case 3:
                  		tecla='sqrt(';
                      str1+=tecla;
                      dfplayer.play(9);
                      delay(1000);
                      break;
                  	case 10:
                  		tecla='(';
                      str1+=tecla;
                      dfplayer.play(2);
                      break;
                  	case 11:
                  		tecla=')';
                      str1+=tecla;
                      dfplayer.play(53);
                      break;
                    case 12:
                  		tecla='p';
                      dfplayer.play(6);
                      break;
                  	case 13:
                  		tecla='%';
                      str1+=tecla;
                      dfplayer.play(56);
                      break;                  	
                  	case 20:                  	
                  		tecla = '7';
                      str1+=tecla;
                      dfplayer.play(16);
                      break;
                  	case 21:                  	
                  		tecla = '8';
                      str1+=tecla;
                      dfplayer.play(17);
                      break;
                  	case 22:
                  		tecla = '9';
                      str1+=tecla;
                      dfplayer.play(18);
                      break;
                  	case 23:
                  		tecla = '+';
                      str1+=tecla;
                      dfplayer.play(54);
                      break;                	
                  	case 30:
                  		tecla = '4';
                      str1+=tecla;
                      dfplayer.play(13);
                      break;
                  	case 31:
                  		tecla = '5';
                      str1+=tecla;
                      dfplayer.play(14);
                      break;
                  	case 32:
                  		tecla = '6';
                      str1+=tecla;
                      dfplayer.play(15);
                      break;
                  	case 33:
                  		tecla = '-';
                      str1+=tecla;
                      dfplayer.play(55);
                      break;        	
                  	case 40:
                  		tecla='1';
                      str1+=tecla;
                      dfplayer.play(10);
                      break;
                  	case 41:
                  		tecla='2';
                      str1+=tecla;
                      dfplayer.play(11);
                      break;
                  	case 42:
                  		tecla='3';
                      str1+=tecla;
                      dfplayer.play(12);break;
                  	case 43:
                  		tecla='*';str1+=tecla;
                      dfplayer.play(1);break;

                  	case 50:
                  		tecla ='='; //Define a tecla como '='
                      res = te_interp(str1.c_str(), &error); //String str1 é utilizada na função te_interp da Tiniexpr e retorna erro ou o resultado da expressão
                      // Se não houver erros na interpretação da expressão
                      if(error == 0){ 
                        Serial.print("Result: ");
                        Serial.println(res, 2); //Printa o resultado da expressão com 2 casas decimais no Serial
                        str1=""; // Limpa a string str1
                        }
                      //Se der erro na expressão
                      else{
                        // Printa espaços para posicionar o indicador de erro (^~~) logo abaixo do local do erro na expressão
                        while(--error) Serial.print(' ');
                        Serial.println("^~~"); //Printa o indicador de erro (^~~) no terminal serial
                        Serial.println("Error in expression"); //Printa uma mensagem de erro no terminal serial indicando que houve um erro na expressão
                      }
                      break;
                  	case 51:
                  		tecla='0';str1.concat(tecla);
                      dfplayer.play(8);break;
                  	case 52:
                  		tecla=',';str1.concat(tecla);
                      dfplayer.play(7);break;
                  	case 53:
                  		tecla='/';str1.concat(tecla);
                      dfplayer.play(5);break;
                }
              lcd.print(str1);  //Exibe o conteúdo da string str1 no display LCD  
              count2++; //Incrementa o contador de ações realizadas
            }
          //Método para não duplicar tecla, verifica se os 24 botões foram percorridos e se a variável tecla é diferente de 'h'
          if (count==24 && tecla!='h'){
          	tecla='h'; //Reinicia a variável tecla
          }
        }
        coluna = -1; //Reinicia o contador de coluna
    }
}