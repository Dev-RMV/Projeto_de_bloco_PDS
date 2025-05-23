# Leitor de Tensão com Display OLED 128x64

Este projeto utiliza um microcontrolador (como o Arduino Uno) para ler sinais analógicos de uma entrada (pino A0), calcular características da onda como tensão de pico (Vp), valor médio (Vavg), valor eficaz (Vrms), tensão mínima (Vmin) e tensão pico a pico (Vpp), e exibi-las em um display OLED 128x64 monocromático.

## Componentes Utilizados

- **Microcontrolador:** Arduino Uno ou compatível  
- **Display OLED:** Adafruit Monochrome 128×64 (I2C)  
- **Sensor ou fonte de sinal analógico** conectada ao pino A0  
- **Bibliotecas:**
  - [`Adafruit_SSD1306`](https://github.com/adafruit/Adafruit_SSD1306)
  - [`Adafruit_GFX`](https://github.com/adafruit/Adafruit-GFX-Library)

## Funcionalidade

O programa realiza cerca de 5000 amostragens da entrada analógica, determinando os valores máximo e mínimo para calcular os seguintes parâmetros elétricos:

- **Vp (Tensão de Pico)**
- **Vpp (Tensão Pico a Pico)**
- **Vrms (Valor Eficaz)**
- **Vavg (Valor Médio)**
- **Vmin (Tensão Mínima)**

Esses valores são exibidos em tempo real no display OLED I2C, utilizando as bibliotecas da Adafruit, que facilitam a manipulação gráfica com comandos como `display.setCursor()` e `display.print()`.

## Instalação

1. Instale as bibliotecas necessárias através do **Gerenciador de Bibliotecas** da IDE do Arduino:
   - `Adafruit SSD1306`
   - `Adafruit GFX Library`

2. Conecte o display OLED aos pinos I2C do Arduino (normalmente A4 - SDA, A5 - SCL).

3. Faça o upload do código para o seu Arduino.

## Notas Técnicas

- O endereço padrão do display I2C é `0x3C`.
- Recomenda-se ao menos **1 KB de RAM disponível** para armazenar o buffer gráfico da tela, conforme indicado pela documentação da **Adafruit**:

  > “Bibliotecas como a Adafruit_SSD1306 e Adafruit_GFX permitem inicializar o display em poucos comandos (`display.begin(SSD1306_SWITCHCAPVCC, 0x3C);`) e desenhar textos ou gráficos diretamente com funções como `display.setCursor()` e `display.print()`. Recomenda-se buffer de RAM de 1 KB para a tela completa.”  
  > — *ADAFT781 – Adafruit Monochrome 128×64 OLED Graphic Display, Adafruit Learning System, 2020.*

## Observações

- O código realiza uma compensação do OFFSET da leitura analógica com base nos valores máximos e mínimos medidos, assumindo que a tensão de referência ideal do sinal AC deveria estar em 511,5 (meio do range de 10 bits do ADC).
- A inicialização do display está localizada dentro do `loop()`, o que pode causar reinicializações constantes — o ideal seria mover `display.begin()` para dentro da função `setup()`.

## Aplicação Científica

Este projeto foi desenvolvido no contexto de um artigo científico. O `README.md` serve também como material complementar para fins acadêmicos.  
**Autores:** [Rodrigo das Mercês Vianna, João Rafael Broz dos Santos, Guilherme Saraiva Gomes de Carvalho]  
**Orientador:** [Vitor Amadeu Souza]  
**Instituição:** [Instituto Infnet]

---
