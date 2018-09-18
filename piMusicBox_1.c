#include "piMusicBox_1.h"

int GPIO_PWM = 18; // generador onda cuadrada
int GPIO_RFIDQ = 5; //entrada GPIO_RFIDQ
//#define GPIO_RFIDQ     5 //A DEFINIR

//int GPIO_SPI_MISO = 9; //entrada lector_RFID  Creo q solo esta
#define GPIO_REDLED     21 //A DEFINIR
#define GPIO_GREENLED   12

volatile int flags = 0;
int debounceTime;
int frecuenciaGOT[518] = {1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,1175,0,1397,0,932,0,1244,0,1175,0,1397,0,932,0,1244,0,1175,0,1046,0,831,0,698,0,523,0,349,0,784,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,587,0,622,0,587,0,523,0,587,0,784,0,880,0,932,0,1046,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1046,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,880,0,784,0,932,0,1244,0,0,1397,0,0,932,0,0,1175,0,0,1244,0,0,1175,0,0,932,0,0,1046,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,0,0,0,2794,0,0,0,0,3136,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,1397,0,0,0,2350,0,0,0,2489,0,0,0,2350,0,0,0,0,2093,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865};
int tiempoGOT[518] = {900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1400,1400,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,116,267,28,267,28,267,28,900,89,900,89,1400,89,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,69,7,69,7,69,7,69,7,267,28,400,45,133,13,267,28,267,28,267,28,300,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,900,89,900,133,13,150,133,13,150,1200,1800,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,267,28,1200,400,133,13,133,13,150,900,89,900,900,89,900,600,59,600,267,28,300,600,59,600,267,28,300,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,133,13,267,28,267,28,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,900,89,900,900,900,900,89,900,900,900,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,600,212,133,13,150,150,267,28,300,300,400,45,450,450,133,13,150,150,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400,116,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400};
int frecuenciaTetris[55] = {1319,988,1047,1175,1047,988,880,880,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,1175,1397,1760,1568,1397,1319,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,659,523,587,494,523,440,415,659,523,587,494,523,659,880,831};
int tiempoTetris[55] = {450,225,225,450,225,225,450,225,225,450,225,225,450,225,225,450,450,450,450,450,675,450,225,450,225,225,675,225,450,225,225,450,225,225,450,450,450,450,450,450,900,900,900,900,900,900,1800,900,900,900,900,450,450,900,1800};
int frecuenciaStarwars[59] = {523,0,523,0,523,0,698,0,1046,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,1760,0,0,784,0,523,0,0,523,0,0,523,0};
int tiempoStarwars[59] = {134,134,134,134,134,134,536,134,536,134,134,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,429,357,1071,268,67,67,268,67,67,67,67,67};
int frecuenciaDespacito[160] = {0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,0,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318,659,659,659,659,659,659,659,659,554,587,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318};
int tiempoDespacito[160] =  {150,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,800,300,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,450,1800,150,150,150,150,300,150,300,150,150,150,300,150,300,450,450,300,150,150,225,75,150,150,300,450,800,150,150,300,150,150,300,450,150,150,150,150,150,150,150,150,300,300,150,150,150,150,150,150,450,150,150,150,300,150,300,450,450,300,150,150,150,300,150,300,450,800,150,150,300,150,150,300,450};
//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------

int
systemSetup (void) {
	// sets up the wiringPi library
	piLock (STD_IO_BUFFER_KEY);
	if (wiringPiSetupGpio () < 0) {
		printf ("Unable to setup wiringPi\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
	}
	piUnlock (STD_IO_BUFFER_KEY);
	initialize_rfid();//si  una system setup si no aqui
	pinMode(GPIO_RFIDQ, INPUT);
	pinMode(GPIO_GREENLED , OUTPUT);
	pinMode(GPIO_REDLED   , OUTPUT);
	softToneCreate(GPIO_PWM);
	return 1;
}

void
cleanLocalFlag(int whichFlag){
	piLock (FLAGS_KEY);
	flags &= ~whichFlag;
	piUnlock (FLAGS_KEY);
}

void
setLocalFlag(int nameFlag){
	piLock(FLAGS_KEY);
	flags |= nameFlag;
	piUnlock(FLAGS_KEY);
}

void
resetLocalFlag(){
	cleanLocalFlag (FLAG_PLAYER_START);
	cleanLocalFlag (FLAG_PLAYER_STOP);
	cleanLocalFlag (FLAG_PLAYER_END);
	cleanLocalFlag (FLAG_NOTA_TIMEOUT);
}

void
resetLocalFlagCard(){
	cleanLocalFlag (FLAG_SYSTEM_START);
	cleanLocalFlag (FLAG_CARD_IN);
	cleanLocalFlag (FLAG_VALID_CARD);
	cleanLocalFlag (FLAG_SYSTEM_END);
}

void
setLocalBuffer(char *bf){
	piLock (STD_IO_BUFFER_KEY);
	printf("%s",bf);
	piUnlock (STD_IO_BUFFER_KEY);
}

int
getLocalFlag(int whichFlag){
	int result = 0;
	piLock(FLAGS_KEY);
	result = (flags & whichFlag);
	piUnlock(FLAGS_KEY);
	return result;
}

char *getUID(){
	return read_id();
}

void
fsm_setup(fsm_t* player_fsm) {
	resetLocalFlag();
	setLocalBuffer("\nComienza player...\n");
}

void
fsm_setup_card(fsm_t* card_fsm) {
	resetLocalFlagCard();
	setLocalBuffer("\nComienza card...\n");
	setLocalFlag(FLAG_SYSTEM_START);
}

//---------------- Condiciones disparo PLAYER------------

int
CompruebaPlayerStart (fsm_t* this) {
	return getLocalFlag(FLAG_PLAYER_START);
}

int
CompruebaPlayerStop (fsm_t* this) {
	return !getLocalFlag(FLAG_CARD_IN);
}

int
CompruebaNuevaNota (fsm_t* this) {
	return !getLocalFlag(FLAG_PLAYER_END);
}

int
CompruebaFinalMelodia (fsm_t* this) {
	return !CompruebaNuevaNota(this);
}

int
CompruebaNotaTimeout (fsm_t* this) {
	return getLocalFlag(FLAG_NOTA_TIMEOUT);
}

//--------------- Condiciones disparo CARD---------------

int
CompruebaComienzo (fsm_t* this) {
	if (CompruebaTarjetaNoDisponible(this)){
		setLocalFlag(FLAG_SYSTEM_START);
	}
	return  getLocalFlag(FLAG_SYSTEM_START);
}

int
CompruebaTarjetaDisponible (fsm_t* this) {
	if(digitalRead(GPIO_RFIDQ)){
		setLocalFlag(FLAG_CARD_IN);
	}
    else {
	    cleanLocalFlag(FLAG_CARD_IN);
    }
	return getLocalFlag(FLAG_CARD_IN);
}

int
CompruebaTarjetaNoDisponible (fsm_t* this) {
	return !CompruebaTarjetaDisponible(this);
}

int
CompruebaTarjetaValida(fsm_t* this) {
	return getLocalFlag(FLAG_VALID_CARD);
}

int
CompruebaTarjetaNoValida(fsm_t* this) {
	return !CompruebaTarjetaValida(this);
}

int
CompruebaFinalReproduccion (fsm_t* this) {
	return getLocalFlag(FLAG_SYSTEM_END);
}

//-------------------- Acciones PLAYER --------------------------------------------

void
fromTimeout (void) {
	setLocalFlag(FLAG_NOTA_TIMEOUT);
}

void
InicializaMelodia (fsm_t *this){
  TipoSistema *tsistema = (TipoSistema * )(this->user_data);
	TipoPlayer *player = &(tsistema->player);
	player->posicion_nota_actual = -1;
	player->melodia = &(tsistema->tarjetas_activas[tsistema->pos_tarjeta_actual].melodia);
  player->tempo = tmr_new ((void *)fromTimeout);
}

void
InicializaPlayer (fsm_t* this) {
	TipoPlayer *p_player = (TipoPlayer*)(this-> user_data);
	cleanLocalFlag(FLAG_PLAYER_START);
	setLocalFlag(FLAG_NOTA_TIMEOUT);
	p_player->posicion_nota_actual = -1;
}

void
ActualizaPlayer (fsm_t* this) {
	TipoPlayer *p_player = (TipoPlayer*) this-> user_data;
	cleanLocalFlag(FLAG_NOTA_TIMEOUT);
	p_player->posicion_nota_actual +=1;

	if (p_player->posicion_nota_actual>=p_player->melodia->num_notas) {
		setLocalBuffer("\nFinal de la melodia\n");
		setLocalFlag(FLAG_PLAYER_END);
	}
	else {
		p_player->frecuencia_nota_actual = p_player->melodia->frecuencias[p_player->posicion_nota_actual];
		p_player->duracion_nota_actual = p_player->melodia->duraciones[p_player->posicion_nota_actual];

		char linea[200];
		sprintf(linea,"[Player][Actualiza player][Nueva nota [%d]/[%d]]\n",p_player->posicion_nota_actual,p_player->melodia->num_notas);
		setLocalBuffer(linea);
	}
}

void
StopPlayer (fsm_t* this) {
	cleanLocalFlag(FLAG_CARD_IN);
	softToneWrite(GPIO_PWM, 0);
}

void
FinalMelodia (fsm_t* this) {
	cleanLocalFlag(FLAG_PLAYER_END);
	softToneWrite(GPIO_PWM, 0);
	setLocalFlag(FLAG_SYSTEM_END);
}

void
PlayNota (fsm_t* this) {
	cleanLocalFlag(FLAG_PLAYER_END);
	TipoPlayer *p_player = (TipoPlayer*)(this-> user_data);
	softToneWrite(GPIO_PWM, p_player->frecuencia_nota_actual);
	tmr_startms(p_player->tempo, p_player->duracion_nota_actual);
	char linea[200];
	sprintf(linea,"[Player][ComienzaNuevaNota][Nota [%d]][Frec [%d]][Dura [%d]]]\n",p_player->posicion_nota_actual,p_player->frecuencia_nota_actual,p_player->duracion_nota_actual);
	setLocalBuffer(linea);
}

//-------------------- Acciones CARD --------------------------------------------

void
ComienzaSistema (fsm_t* this) {
	cleanLocalFlag(FLAG_SYSTEM_START);
}

void
LeerTarjeta (fsm_t* this) {
	cleanLocalFlag(FLAG_CARD_IN);
	TipoSistema *tsistema = (TipoSistema * )(this->user_data);
	char *mi_id = getUID();
    int i;
    for (i=0; i< tsistema->num_tarjetas_activas;i++){
     	if (!strcmp(mi_id,tsistema->tarjetas_activas[i].uid)){
     		tsistema->pos_tarjeta_actual = i;
     		strcpy(tsistema->uid_tarjeta_actual_string,tsistema->tarjetas_activas[i].uid);
				InicializaMelodia(this);
				setLocalBuffer("\nIts a valid card\n");
				setId(GPIO_GREENLED);
				setLocalFlag(FLAG_VALID_CARD);
				return;
     	}
    }
		setLocalBuffer("\nNOT valid card\n");
		cleanLocalFlag(FLAG_VALID_CARD);
}

void
DescartaTarjeta (fsm_t* this) {
	cleanLocalFlag(FLAG_VALID_CARD);
	setId(GPIO_REDLED);
}

void
ComienzaReproduccion(fsm_t* this) {
	cleanLocalFlag(FLAG_VALID_CARD);
	setLocalFlag(FLAG_PLAYER_START);
}

void
CancelaReproduccion(fsm_t* this) {
	cleanLocalFlag(FLAG_CARD_IN);
	setLocalFlag(FLAG_PLAYER_STOP);
}

void
FinalizaReproduccion(fsm_t* this) {
	cleanLocalFlag(FLAG_SYSTEM_END);
}

//-------------------- Funciones Auxiliares -------------------------------
// espera hasta la próxima activación del reloj
void
delay_until (unsigned int next) {
	unsigned int now = millis();
	if (next > now) {
		delay (next - now);
	}
}

void
transformada(TipoMelodia* tm, int cont, int* frecuencias, int* duraciones){
	int i;
	for (i = 0; i < cont; ++i){
		tm->frecuencias[i]=frecuencias[i];
		tm->duraciones[i] = duraciones[i];
	}
	tm->num_notas=cont;
}

void
loadMelodias(TipoSistema *tpsist){

	strcpy(tpsist->tarjetas_activas[0].uid,"09090791");
	strcpy(tpsist->tarjetas_activas[0].melodia.nombre,"GOT");
	transformada(&(tpsist->tarjetas_activas[0].melodia),518,frecuenciaGOT,tiempoGOT);

	strcpy(tpsist->tarjetas_activas[1].uid,"19090791");
	strcpy(tpsist->tarjetas_activas[1].melodia.nombre,"TETRIS");
	transformada(&(tpsist->tarjetas_activas[1].melodia),55,frecuenciaTetris,tiempoTetris);

	strcpy(tpsist->tarjetas_activas[2].uid,"29090791");
	strcpy(tpsist->tarjetas_activas[2].melodia.nombre,"STARWARS");
	transformada(&(tpsist->tarjetas_activas[2].melodia),59,frecuenciaStarwars,tiempoStarwars);

	strcpy(tpsist->tarjetas_activas[3].uid,"39090791");
	strcpy(tpsist->tarjetas_activas[3].melodia.nombre,"DESPACITO");
	transformada(&(tpsist->tarjetas_activas[3].melodia),160,frecuenciaDespacito,tiempoDespacito);

	tpsist->num_tarjetas_activas = 4;
	*(tpsist->uid_tarjeta_actual_string)='\0';
}

void
setId(int pin){
	digitalWrite(pin,1);
	delay(2000);
	digitalWrite(pin,0);
	delay(500);
}

//----------------------------- MAIN --------------------------------------------
int
main (){
	unsigned int next;
	TipoSistema sistema;
  loadMelodias(&sistema);

	fsm_trans_t transCard[] = {
			{ WAIT_START, CompruebaComienzo 		  		, WAIT_CARD , ComienzaSistema 	 	 },
			{ WAIT_CARD , CompruebaTarjetaDisponible  , WAIT_CHECK, LeerTarjeta  		 		 },
			{ WAIT_CHECK, CompruebaTarjetaNoValida    , WAIT_CARD , DescartaTarjeta      },
			{ WAIT_CHECK, CompruebaTarjetaValida	  	, WAIT_PLAY , ComienzaReproduccion },
			{ WAIT_PLAY , CompruebaTarjetaNoDisponible, WAIT_START, CancelaReproduccion  },
			{ WAIT_PLAY , CompruebaFinalReproduccion  , WAIT_START, FinalizaReproduccion },
			{-1, NULL, -1, NULL },
	};
	fsm_trans_t transReproductor[] = {
			{ WAIT_START, CompruebaPlayerStart , WAIT_NEXT , InicializaPlayer },
			{ WAIT_NEXT , CompruebaPlayerStop  , WAIT_START, StopPlayer       },
			{ WAIT_NEXT , CompruebaNotaTimeout , WAIT_END  , ActualizaPlayer  },
			{ WAIT_END  , CompruebaNuevaNota   , WAIT_NEXT , PlayNota         },
			{ WAIT_END  , CompruebaFinalMelodia, WAIT_START, FinalMelodia     },
			{-1, NULL, -1, NULL },
	};

	fsm_t* card_fsm = fsm_new (WAIT_START, transCard, &(sistema));
	fsm_t* player_fsm = fsm_new (WAIT_START, transReproductor, &(sistema));

	systemSetup();
	fsm_setup_card (card_fsm);
	fsm_setup (player_fsm);

	next = millis();

	while (1) {
		fsm_fire (card_fsm);
		fsm_fire (player_fsm);
		next += CLK_MS;
		delay_until (next);
	}
	fsm_destroy (player_fsm);
	fsm_destroy (card_fsm);
}
