/*
 * piMusicBox_1.h
 *
 *  Created on: 15 de feb. de 2018
 *      Author: Rodrigo
 */

#ifndef PIMUSICBOX_1_H_
#define PIMUSICBOX_1_H_

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softTone.h>
#include "fsm.h"
#include "tmr.h"
#include "rfid.h"

extern int frecuenciaGOT[];
extern int tiempoGOT[];
extern int frecuenciaTetris[];
extern int tiempoTetris[];
extern int frecuenciaStarwars[];
extern int tiempoStarwars[];
extern int frecuenciaDespacito[];
extern int tiempoDespacito[];

typedef enum {
	WAIT_START=0, //revisar
	WAIT_NEXT,
	WAIT_END,
	WAIT_CARD,
	WAIT_CHECK,
	WAIT_PLAY
} TipoEstadosSistema;

char *TipoEstadosSistemaStr[]={
	"WAIT_START",
	"WAIT_NEXT",
	"WAIT_END",
	"WAIT_CARD",
	"WAIT_CHECK",
	"WAIT_PLAY"
};

#define MAX_NUM_TARJETAS	5
#define MAX_NUM_NOTAS 		600
#define MAX_NUM_CHAR_NOMBRE	100
#define MAX_NUM_CHAR_UID	100

// PERIODO DE ACTUALIZACION DE LA MAQUINA ESTADOS
#define CLK_MS 				10

// FLAGS DEL SISTEMA
#define FLAG_PLAYER_START   0x01
#define FLAG_PLAYER_STOP    0x02
#define FLAG_PLAYER_END 	0x04
#define FLAG_NOTA_TIMEOUT	0x08

#define FLAG_SYSTEM_START   0x10
#define FLAG_CARD_IN  		0x20
#define FLAG_VALID_CARD 	0x40
#define FLAG_SYSTEM_END		0x80


// A 'key' which we can lock and unlock - values are 0 through 3
//	This is interpreted internally as a pthread_mutex by wiringPi
//	which is hiding some of that to make life simple.
#define	FLAGS_KEY	        1
#define	STD_IO_BUFFER_KEY	2
#define Uid int

typedef struct {
	char nombre[MAX_NUM_CHAR_NOMBRE]; // String con el nombre de la melodia
	int frecuencias[MAX_NUM_NOTAS]; // Array con las frecuencias de las notas de la melodia
	int duraciones[MAX_NUM_NOTAS]; // Array con las duraciones de las notas de la melodia
	int num_notas; // Numero de notas de que consta la melodia
} TipoMelodia;

typedef struct {
	int posicion_nota_actual;	// Valor correspondiente a la posicion de la nota actual en los arrays de frecuencias y duraciones
	int frecuencia_nota_actual; // Valor correspondiente a la frecuencia de la nota actual
	int duracion_nota_actual; // Valor correspondiente a la duracion de la nota actual
	tmr_t* tempo;
	TipoMelodia* melodia;
} TipoPlayer;

typedef struct {
   char uid [MAX_NUM_CHAR_UID];
// Uid uid;  // Identificador correspondiente a la tarjeta (tipo de datos complejo definido en liberia control RFID)
	TipoMelodia melodia;
} TipoTarjeta;

typedef struct {
	TipoPlayer player; // Reproductor de melodias
	int num_tarjetas_activas; // Numero de tarjetas validas
	TipoTarjeta tarjetas_activas[MAX_NUM_TARJETAS]; // Array con todas las tarjetas validas
	//Uid uid_tarjeta_actual; // Identificador de la tarjeta actual (tipo de datos complejo definido en liberia control RFID)
	int pos_tarjeta_actual; // Posicion de la tarjeta actual en el array de tarjetas validas
	char uid_tarjeta_actual_string[MAX_NUM_CHAR_UID]; // Identificador de la tarjeta actual a modo de string de caracteres
} TipoSistema;
/*
int InicializaMelodia (TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas);
int systemSetup (void);
void fsm_setup(fsm_t* player_fsm);
void fsm_setup_card(fsm_t* card_fsm);
//-------------------- Condiciones de disparo-------------------------------
int CompruebaPlayerStart (fsm_t*);
int CompruebaPlayerStop (fsm_t*);
int CompruebaFinalMelodia (fsm_t*);
int CompruebaNuevaNota (fsm_t*);

int CompruebaComienzo (fsm_t*);
int CompruebaTarjetaDisponible (fsm_t*);
int CompruebaTarjetaNoDisponible (fsm_t*);
int CompruebaTarjetaNoValida (fsm_t*);
int CompruebaTarjetaValida (fsm_t*);
int CompruebaFinalReproduccion (fsm_t*);
//-------------------- Acciones --------------------------------------------
void InicializaPlayer (fsm_t*);
void ActualizaPlayer (fsm_t*);
void StopPlayer (fsm_t*);
void ComienzaNuevaNota(fsm_t*);
void FinalMelodia(fsm_t*);
void PlayNota (fsm_t*);

void ComienzaSistema (fsm_t*);
void LeerTarjeta (fsm_t*);
void DescartaTarjeta(fsm_t*);
void ComienzaReproduccion(fsm_t*);
void CancelaReproduccion(fsm_t*);
void FinalizaReproduccion(fsm_t*);
*/
#endif /* PIMUSICBOX_1_H_ */
