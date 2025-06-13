# Tarefa 02 - Comunicação entre Processos  
**Disciplina:** PET2049 - Sistemas Operacionais - T01 (2025.1 - 23M45)  
**Professor:** Reudismam Rolim  


## Descrição

Esta tarefa tem como objetivo simular a **comunicação entre processos (IPC)**, utilizando pelo menos dois processos distintos: **um cliente e um servidor**. Utilizamos a linguagem **Python** para implementar a solução, com comunicação realizada via **sockets TCP/IP**.

---

## Objetivos

- Compreender os fundamentos da comunicação entre processos.
- Desenvolver um modelo cliente-servidor funcional.
- Aplicar conceitos de IPC com sockets em rede local.

---

## Mecanismo de Comunicação Utilizado

A comunicação entre os processos foi implementada usando **sockets TCP/IP**, onde:

- O **servidor** fica escutando uma porta TCP específica aguardando conexões.
- O **cliente** se conecta ao servidor e envia mensagens.
- O servidor processa a requisição e envia uma resposta.

Este modelo simula um cenário real de rede local, com troca de mensagens síncronas.

---

## 📁 Estrutura do Projeto
- cliente.c # Código do processo cliente
- servidor.c # Código do processo servidor

