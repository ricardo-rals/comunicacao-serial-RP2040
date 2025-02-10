# Projeto de Comunicação Serial com RP2040

## Descrição

Este projeto foi desenvolvido para consolidar os conceitos sobre o uso de interfaces de comunicação serial no microcontrolador RP2040 e explorar as funcionalidades da placa de desenvolvimento BitDogLab. O objetivo é manipular e controlar LEDs comuns e LEDs endereçáveis WS2812, além de implementar a interação com botões e um display SSD1306 via I2C.

## Componentes Utilizados

- Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.
- LED RGB, com os pinos conectados às GPIOs 11, 12 e 13.
- Botão A conectado à GPIO 5.
- Botão B conectado à GPIO 6.
- Display SSD1306 conectado via I2C (GPIO 14 e GPIO 15).

## Funcionalidades do Projeto

1. **Modificação da Biblioteca `font.h`**
   - Adição de caracteres minúsculos à biblioteca `font.h`. Criatividade na criação de novos caracteres é incentivada.

2. **Entrada de Caracteres via PC**
   - Utilização do Serial Monitor do VS Code para digitar caracteres.
   - Cada caractere digitado no Serial Monitor é exibido no display SSD1306.
   - Quando um número entre 0 e 9 é digitado, um símbolo correspondente ao número é exibido na matriz 5x5 WS2812.

3. **Interação com o Botão A**
   - Pressionar o botão A alterna o estado do LED RGB Verde (ligado/desligado).
   - Uma mensagem informativa sobre o estado do LED é exibida no display SSD1306.
   - Um texto descritivo sobre a operação é enviado ao Serial Monitor.

4. **Interação com o Botão B**
   - Pressionar o botão B alterna o estado do LED RGB Azul (ligado/desligado).
   - Uma mensagem informativa sobre o estado do LED é exibida no display SSD1306.
   - Um texto descritivo sobre a operação é enviado ao Serial Monitor.

## Requisitos do Projeto

1. **Uso de Interrupções**
   - Todas as funcionalidades relacionadas aos botões são implementadas utilizando rotinas de interrupção (IRQ).

2. **Debouncing**
   - Implementação do tratamento do bouncing dos botões via software.

3. **Controle de LEDs**
   - O projeto inclui o uso de LEDs comuns e LEDs WS2812, demonstrando o domínio de diferentes tipos de controle.

4. **Utilização do Display 128 x 64**
   - Utilização de fontes maiúsculas e minúsculas, demonstrando o domínio do uso de bibliotecas e o entendimento do funcionamento do display, bem como a utilização do protocolo I2C.

5. **Envio de Informação pela UART**
   - Compreensão sobre a comunicação serial via UART.

6. **Organização do Código**
   - O código está bem estruturado e comentado para facilitar o entendimento.

## Instalação

1. Clone o repositório:
   ```bash
   git clone https://github.com/ricardo-rals/comunicacao-serial-RP2040.git
   cd comunicacao-serial-RP2040
   ```

2. Abra o projeto no Visual Studio Code.

3. Configure o SDK do Raspberry Pi Pico W de acordo com a [documentação oficial](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf).

4. Siga as instruções no Visual Studio Code para compilar e carregar o projeto no seu Raspberry Pi Pico.

## Video de Apresentação

Para um guia visual sobre como configurar e executar este projeto, confira este.
[YouTube video](https://youtu.be/63urmSieZVo).
