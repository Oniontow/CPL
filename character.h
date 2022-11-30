#ifndef _CHARACTER_H
#define _CHARACTER_H



#ifndef _ATTRIBUTE
#define _ATTRIBUTE
enum attribute{
	fire,
	water,
	grass
};
#endif

enum effect{
	health_to_attack,	// attack increases while losing health
	swifty,  			// high avoid rate
	armored,			// high defence 
	stun,				// tend to stun student	  (stun every 3 rounds)
	firing,				// tend to ignite student (ignite every 6 rounds)
	
};


class student_class{						// class of the main character (student) 
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
		
		student_class();
		void init();
		
		int get_health_limit();				//���o��q�W�� 
		void raise_health_limit(double);	//������q�W�� 
		
		bool alive();						//�^�ǬO��(true)�O��(false) 
		
		void hurt(double);					//���˪���ơA��J���쪺�ˮ`�A�g�L���m�p���ק��q 
};

class professor_class{					//class of enemy
	
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
		int ignite_counter;
		int stun_counter;
		
		professor_class(int a = 0);
		attribute get_attribute() { return element; }	//�^���ݩ� 
		bool alive() { return living; }					//�^�ǬO�_�ͦs 
		
		//void hurt(double);							//�]���٤��T�w�ݩʬ۫g�n���g�A�ڴN�����g 
};



#endif
