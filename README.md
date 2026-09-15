# Monitoramento de Temperatura e Umidade via SNMP

Projeto pessoal para coleta de temperatura e umidade com Arduino, Ethernet Shield W5100 e sensor DHT22, integrado ao Zabbix por SNMP.

## Funcionamento

O código implementa um agente SNMP que:

- responde a requisições `GET` do servidor Zabbix;
- lê o sensor DHT22 a cada cinco segundos;
- mantém a última leitura válida em memória para evitar bloqueios durante as requisições;
- disponibiliza OIDs personalizadas para temperatura e umidade.

## Hardware

- Arduino Uno ou Mega
- Ethernet Shield W5100
- Sensor DHT22
- Cabo de rede

## Bibliotecas

- `SPI.h` — incluída na IDE do Arduino
- `Ethernet.h` — incluída na IDE do Arduino
- `DHT.h` — biblioteca para o sensor DHT22
- `Agentuino.h` — agente SNMP para Arduino

## Configuração

O exemplo utiliza o endereço IP privado `192.168.0.100`. Ajuste-o no arquivo `zabbix_snmp_dht22.ino` para a rede do ambiente de teste antes da compilação.

1. Instale as bibliotecas necessárias na IDE do Arduino.
2. Conecte o Ethernet Shield W5100 e o sensor DHT22 ao Arduino.
3. Revise o endereço IP definido no código.
4. Compile e grave o arquivo `zabbix_snmp_dht22.ino`.
5. No Zabbix, crie um host com interface SNMP usando o endereço configurado.
6. Adicione os itens de monitoramento com as OIDs abaixo.

## OIDs

| Métrica | OID | Tipo |
|---|---|---|
| Temperatura | `1.3.6.1.4.1.12345.1.0` | `OCTET STRING` |
| Umidade | `1.3.6.1.4.1.12345.2.0` | `OCTET STRING` |

Os valores são retornados como texto. No Zabbix, use pré-processamento quando for necessário convertê-los para valor numérico.

## Estrutura

- `zabbix_snmp_dht22.ino` — código do agente SNMP e leitura do sensor.
- `README.md` — documentação do projeto.

## Escopo

O repositório apresenta uma implementação de estudo e não inclui template do Zabbix, diagrama de ligação, screenshots ou validação documentada em ambiente de produção.
