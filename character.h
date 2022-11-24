enum attribute{
	fire,
	water,
	grass
};
enum effect{
	health_to_attack,	// attack increases while losing health
	swifty,  			// high avoid rate
	armored,			// high defence 
	stun,				// tend to stun student	  (stun every 3 rounds)
	firing,				// tend to ignite student (ignite every 6 rounds)
	
};

class student{						// class of the main character (student) 
	private:
		int health_limit;
		bool living;
	public:
		int health;
		int shield;	
		int defence;
		double attack_rate;
		double hit_rate;
		double avoid_rate;
		bool burning;
		bool stunning;
		
		student();
		void init();
		
		int get_health_limit();				//���o��q�W�� 
		void raise_health_limit(double);	//������q�W�� 
		
		bool alive();						//�^�ǬO��(true)�O��(false) 
		
		void hurt(double);					//���˪���ơA��J���쪺�ˮ`�A�g�L���m�p���ק��q 
};
student::student(){
	health_limit = 100;
	living = true;
	
	health = 100;
	shield = 0;
	defence = 0;
	attack_rate = 1;
	hit_rate = 0.9;
	avoid_rate = 0.1;
	burning = false;
	stunning = false;
	
}
void student::init(){
	health_limit = 100;
	living = true;
	
	health = 100;
	shield = 0;
	defence = 0;
	attack_rate = 1;
	hit_rate = 0.9;
	avoid_rate = 0.1;
	burning = false;
	stunning = false;
}
int student::get_health_limit(){
	return health_limit;
}
void student::raise_health_limit(double a){
	health_limit += (int)a;
}
void student::hurt(double a){
	
	a = a * ( 100 / (100 + defence) );
	int damage = (int)a;
		
	if(damage > ( health + shield ) ){
		shield = 0;
		health = 0;
		living = false;
	}
	else if(damage > shield){
		shield = 0;
		health -= (damage - shield);
		
	}
	else if(damage < shield){
		shield -= damage;
	}
}
bool student::alive(){
	return living;
}




class professor{					//class of enemy
	
	private:
		int health_limit;
		int difficulty;  			//�Q������ 
		attribute element;			//�ݩ� 
		bool living;
	public:
		int health;
		int shield;
		int attack;	
		int defence;
		double hit_rate;
		double avoid_rate;
		bool burning;
		bool stunning;
		effect special;				//�S��ޯ� 
		
		
		professor(int);
		attribute get_attribute() { return element; }	//�^���ݩ� 
		bool alive() { return living; }					//�^�ǬO�_�ͦs 
		
		//void hurt(double);							//�]���٤��T�w�ݩʬ۫g�n���g�A�ڴN�����g 
};

professor::professor(int a = 0){
	switch(a){
		case 0:
			health_limit = 200;
			difficulty = 1;
			element = water;
			living = true;
			health = health_limit;
			shield = 0;
			attack = 5;
			defence = 400;
			hit_rate = 0.95;
			avoid_rate = 0;
			burning = false;
			stunning = false;
			special = armored;
			break;	
		case 1:
			health_limit = 300;
			difficulty = 2;
			element = grass;
			living = true;
			health = health_limit;
			shield = 0;
			attack = 15;
			defence = 50;
			hit_rate = 0.9;
			avoid_rate = 0.95;
			burning = false;
			stunning = false;
			special = swifty;
			break;
		case 2:
			health_limit = 600;
			difficulty = 3;
			element = fire;
			living = true;
			health = health_limit;
			shield = 0;
			attack = 10;
			defence = 150;
			hit_rate = 0.9;
			avoid_rate = 0.1;
			burning = false;
			stunning = false;
			special = firing;
			break;
			
		case 3:
			health_limit = 1000;
			difficulty = 4;
			element = grass;
			living = true;
			health = health_limit;
			shield = 0;
			attack = 20;
			defence = 50;
			hit_rate = 0.9;
			avoid_rate = 0.1;
			burning = false;
			stunning = false;
			special = stun;
			break;
		case 4:
			health_limit = 500;
			difficulty = 10;
			element = grass;
			living = true;
			health = health_limit;
			shield = 0;
			attack = 20;
			defence = 50;
			hit_rate = 0.9;
			avoid_rate = 0.1;
			burning = false;
			stunning = false;
			special = health_to_attack;
			break;
	}
	
}


