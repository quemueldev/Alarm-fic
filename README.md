# Sistema de Automação do Sinal da Escola

Este projeto consiste no desenvolvimento de um sistema capaz de automatizar o acionamento do sinal da escola de acordo com os horários definidos.
A ideia surgiu a partir da necessidade de reduzir a dependência do acionamento manual do sinal, permitindo que o processo seja realizado automaticamente com base no horário e no calendário escolar.
O projeto está sendo desenvolvido inicialmente como um protótipo utilizando Arduino e um módulo RTC, com a possibilidade de futuramente ser transformado em uma solução própria e adaptada para diferentes escolas.

# Objetivo

Desenvolver um sistema capaz de:

- Acionar o sinal automaticamente nos horários programados;
- Verificar a data e o horário atual;
- Impedir o acionamento em finais de semana;
- Impedir o acionamento em feriados cadastrados;
- Permitir que o sistema seja ativado ou desativado manualmente;
- Manter o controle correto do horário mesmo após uma interrupção na alimentação;
- Evitar que o mesmo horário seja acionado mais de uma vez.

# Funcionamento

O sistema utiliza um **RTC (Real-Time Clock)** para obter a data e o horário atual.
O Arduino compara essas informações com uma lista de horários definidos.
Quando o horário atual corresponde a um dos horários programados, o sistema aciona a saída responsável pelo sinal durante um determinado período.

Antes do acionamento, o sistema também verifica:

1. Se o sistema está ativo;
2. Se a data atual corresponde a algum feriado cadastrado;
3. Se o dia da semana permite o funcionamento;
4. Se o horário atual corresponde a um horário programado;
5. Se o alarme já foi acionado naquele minuto.

# Hardware Protótipo
- Arduino (uno ou nano);
- RTC (DS1307 ou DS3231);
- Switch;
- Cabos de conexão;
- Saída para acionamento do alarme.
