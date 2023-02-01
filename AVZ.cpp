#include "AVZ.hpp"
#include <ctime>
#include <iostream>
#include <sstream>
#include <cassert>
#include "helper.h"
namespace avz
{

	Gameboard::Gameboard():rowCount(),columnCount(), zombieCount(2), objects(rowCount), zombies(0), control(nullptr)//, map(nullptr)
	{
		
		Gameboard(rowCount,columnCount);
	}
	
	Gameboard::Gameboard(const int row, const int column): rowCount(row),columnCount(column) ,zombieCount(2), objects(row),zombies(0), control(nullptr)//, map(nullptr), 
	{
		std::cout << "Gameboard" << std::endl;
		
		std::srand(time(0));
		//int i = 0;
		//for(i=0; i < this->rowCount; ++i)
		//{
		//	this->objects.push_back(std::list<Object>(this->columnCount));
		//}
		//this->map = new Object* [this->rowCount];
		//this->map = (Object**)::operator new (this->rowCount*sizeof (Object*));
		//for(i=0; i < this->columnCount; ++i)
		//{
		//	*(this->map+i) = new Object[this->columnCount];
		//}
		this->randFill();
		this->randFillZombie();
	}

	Gameboard::~Gameboard()
	{
		int i = 0;
		
		// if(this->map!=nullptr)
		// {
			// for(i=0; i < this->rowCount; ++i)
			// {
				
				// delete[] *((this->map)+i);
				
				
			// }
		// }
	}
	
	void Gameboard::setControl(Control* ptr)
	{
		this->control = ptr;
		for(std::list<std::list<Object*> >::iterator it = this->objects.begin();(it!=this->objects.end()); it++)
		{
			for(std::list<Object*>::iterator inner_it = (*it).begin(); (inner_it!=(*it).end()); inner_it++)
			{
				(*inner_it)->setControl(this->control);
			}
		}
	}
	
	void Gameboard::randFill()
	{
		Object* ptr = nullptr;
		int i = 0;
		int j = 0;
		int randomNumber = 0;
		char ch = 0;
		const int attackPower = 20;
		const int healingPoint = 20;
		std::cout << "row=" << this->rowCount << std::endl;
		std::cout<<"columnCount=" << this->columnCount << std::endl;
		//for(i =0; i < this->rowCount; ++i)
			
		for( std::list<std::list<Object*> >::iterator it = this->objects.begin(); it!=this->objects.end(); it++)
		{
			//std::list<Object> object(this->columnCount);
			std::list<Object*>& object = *it;
			for(j=0; j < this->columnCount; ++j)
			{
				randomNumber = std::rand()%8;
				switch(randomNumber)
				{
					case 0:
						ch = '<';
						ptr = new Arrow(attackPower, ch);
						//object.push_back(new Arrow(attackPower, ch));
					break;
					case 1:
						ch = '>';
						ptr = new Arrow(attackPower, ch);
						//object.push_back(new Arrow(attackPower, ch));
					break;
					case 2:
						ch = '^';
						ptr = new Arrow(attackPower, ch);
						//object.push_back(new Arrow(attackPower, ch));
					break;
					case 3:
						ch = 'v';
						ptr = new Arrow(attackPower, ch);
						//object.push_back(new Arrow(attackPower, ch));
					break;
					case 4:
						ch = 'h';
						ptr = new Health(healingPoint);
						//object.push_back(new Health(healingPoint));
					break;
					case 5:
						ch = 'r';
						ptr = new Rock();
						//object.push_back(new Rock());
					break;
					case 6:
						ch = (char)32;
						ptr = new Space();
						//object.push_back(new Space());
					break;
					case 7:
						ch = 'p';
						ptr = new Pod();
						//object.push_back(new Pod());
					break;
					//case 8:
					//	ch = '.';
					//	object.push_back(new Trail());
					//break;
					
				}
				if(ptr!=nullptr)
				{
					ptr->setX(j);
					ptr->setY(i);
					ptr->setControl(this->control);
					object.push_back(ptr);
				}
				//object.back()->setX(j);
				//object.back()->setY(i);
				
			}
			//this->objects.push_back(object);
			++i;
			
		}
	
	}
	
	void Gameboard::randFillZombie()
	{
		int x = 0;
		int y = 0;
		int i = 0;
		bool pending = true;
		int random_range = 3;
		int random_x = 0;
		int random_y = 0;
		int random_life = 0;
		int random_attack = 0;
		Zombie* ptr = nullptr;
		std::cout << "zombieCount = " << this->getZombieCount() << std::endl;
		for(i=0; i < this->getZombieCount(); ++i)
		{
			do
			{
				random_x = std::rand()%this->columnCount;
				random_y = std::rand()%this->rowCount;
			}while((random_x==this->columnCount/2)&&(random_y==this->rowCount/2));
			//std::cout << "random_x="<<random_x <<",random_y="<< random_y << std::endl;
			x = 0;
			y = 0;
			pending = true;
			for(std::list<std::list<Object*> >::iterator it = this->objects.begin();(pending)&&(it!=this->objects.end()); it++)
			{
				if(y==random_y)
				{
					for(std::list<Object*>::iterator inner_it = (*it).begin(); (pending)&&(inner_it!=(*it).end()); inner_it++)
					{
						if(x==random_x)
						{
							ptr = new Zombie(*this,(char) (i+49));
							do
							{
								random_range = std::rand();
								random_life = std::rand()%(*ptr).getMaxLife();
								random_attack = std::rand()%(*ptr).getMaxAttackPower();
								
								if(this->rowCount < this->columnCount)
								{
									random_range = random_range%this->rowCount;
								}
								else
								{
									random_range = random_range%this->columnCount;
								}	
							
							}while((random_range==0)||(random_life==0)||(random_attack==0));
							//std::cout << "zombie " << (char) (i+49) << std::endl;
							//this->zombies.push_back(ptr = new Zombie(*this,(char) (i+49),random_life,random_attack,random_range));
							ptr->setLife(random_life);
							ptr->setAttackPower(random_attack);
							ptr->setAttackRange(random_range);
							ptr->setControl(this->control);
							this->zombies.push_back(ptr);
							ptr->setX(x);
							ptr->setY(y);
							//std::cout << "P" << std::endl;
							//*inner_it = this->zombies.back();
							*inner_it = ptr;
							//std::cout << "P1" << std::endl;
							pending = false;
						}
						++x;
					}
				}
				++y;
			}
		}
	}
	
	
	void Gameboard::placeAlien(Alien& alien, const int x, const int y)
	{
		int posX = x%this->columnCount;
		int posY = y%this->rowCount;
		int i = 0;
		int j = 0;
		bool pending = true;
		
		for(std::list<std::list<Object*> >::iterator it = this->objects.begin();(pending)&&(it!=this->objects.end()); it++)
		{
			if(i==posY)
			{
				for(std::list<Object*>::iterator inner_it = (*it).begin(); (pending)&&(inner_it!=(*it).end()); inner_it++)
				{
					if(j==posX)
					{
						
						//std::cout << "##alien landing at x " << posX <<",posY="<< posY << std::endl;
						alien.setX(posX);
						alien.setY(posY);
						*inner_it = &alien;
						pending = false;
					}
					++j;
				}
			}
			++i;
		}
		
	}
	
	Object& Gameboard::getObjectAt(const int x, const int y)
	{
		int posX = x%this->columnCount;
		int posY = y%this->rowCount;
		int i = 0;
		int j = 0;
		bool pending = true;
		Object* pt = nullptr;
		for(std::list<std::list<Object*> >::iterator it = this->objects.begin();(pending)&&(it!=this->objects.end()); it++)
		{
			if(i==posY)
			{
				for(std::list<Object*>::iterator inner_it = (*it).begin(); (pending)&&(inner_it!=(*it).end()); inner_it++)
				{
					if(j==posX)
					{
						
						//std::cout << "getObject at x " << posX <<",posY="<< posY << std::endl;
						pt = *inner_it;
						
						pending = false;
					}
					++j;
				}
			}
			++i;
		}
		
		return *pt;
	}

	void Gameboard::setObjectAt(Object& object, const int x, const int y)
	{
		int posX = x%this->columnCount;
		int posY = y%this->rowCount;
		int i = 0;
		int j = 0;
		bool pending = true;
		Object* pt = nullptr;
		for(std::list<std::list<Object*> >::iterator it = this->objects.begin();(pending)&&(it!=this->objects.end()); it++)
		{
			if(i==posY)
			{
				for(std::list<Object*>::iterator inner_it = (*it).begin(); (pending)&&(inner_it!=(*it).end()); inner_it++)
				{
					if(j==posX)
					{
						
						//std::cout << "setObject at x " << posX <<",posY="<< posY << std::endl;
						pt = *inner_it;
						//std::cout << "1 setObject at x " << posX <<",posY="<< posY << std::endl;
						*inner_it = &object;
						(*inner_it)->setX(posX);
						(*inner_it)->setY(posY);
						pending = false;
					}
					++j;
				}
			}
			++i;
		}
		
	}
	
	void Gameboard::show() const
	{
		int i =0;
		int j = 0;
		int j1 = 0;
		int j10 = 0;

		std::cout<<".:Alien vs Zombie:."<<std::endl;

		for(std::list< std::list<Object*> >::const_iterator cit = this->objects.cbegin(); cit!=this->objects.end(); cit++ )
		{
			std::cout << ' ';
			for(j1 = 0; j1 < this->columnCount; ++j1)
			{
				std::cout << "+-";
			}
			std::cout << '+' << std::endl;
			std::cout << (i+1);
			j = 0;
			
			for(std::list<Object*>::const_iterator inner_cit = (*cit).cbegin(); inner_cit!=(*cit).end(); inner_cit++)
			{
				std::cout << '|' ;
				(*inner_cit)->show();
				++j;
			}
			++i;
			std::cout << '|' << std::endl;
			
		}
		std::cout << ' ';
		for(j1 = 0; j1 < this->columnCount; ++j1)
		{
			std::cout << "+-";
		}
		std::cout << '+' << std::endl;
		//std::cout << "#j=" << j << std::endl;
		for(j10 = (int)(j/10)+1; j10 >0 ; --j10)
		{
			std::cout << ' ';
			for(j1=0; j1 < ((j10-1)*10)-1; ++j1)			
			{
				std::cout << ' ' << ' ';
			}
			for(; j1 < (j10*10) - 1; ++j1)
			{
				std::cout << ' ' << ((j10==1)?((j1+1)%10):(j10-1));
			}
				
			for(;j1 < ((j10+1)*10)&&(j1< j); ++j1)
			{
				std::cout << ' ' << (j1+1)%10;
			}
			
			std::cout << std::endl;
			
		}
		
		std::cout << std::endl;
		//std::cout << "show i="<< i << ",j="<< j << std::endl;
	}
	
	void Gameboard::refreshAllTrail()
	{
		for(std::list< std::list<Object*> >::iterator it = this->objects.begin(); it!=this->objects.end(); it++ )
		{
			for(std::list<Object*>::iterator inner_it = (*it).begin(); inner_it!=(*it).end(); inner_it++)
			{
				Object& obj = (*inner_it)->reveal();
				Object* pt = *inner_it;
				if((&obj)!=(*inner_it))
				{
					*inner_it = &obj;
					delete pt;
				}
								
			}
		}
		
	}
	
	

	int Gameboard::getRowCount()
	{
		return this->rowCount;
	}

	int Gameboard::getColumnCount()
	{
		return this->columnCount;
	}

	int Gameboard::getZombieCount() const
	{
		return this->zombieCount;
	}
	
	Zombie& Gameboard::getZombie(const int index)
	{
		Zombie* ptr = nullptr;
		int i = 0;
		for(std::list<Zombie*>::iterator it = this->zombies.begin(); it!=this->zombies.end();it++)
		{
			if(i==index)
			{
				ptr = *it;
			}
			++i;
		}
		return *ptr;
	}
	
	Object::Object() : x(0), y(0), symbol('o'), control(nullptr)
	{
		
	}
	
		
	Object::~Object()
	{
		//std::cout << "~~~Object" << std::endl;
	}
	
	char Object::getSymbol() const
	{
		return this->symbol;
	}
	
	
	void Object::setSymbol(const char ch) 
	{
		this->symbol = ch;
	}
	
	int Object::getX()
	{
		return this->x;
	}
	
	int Object::getY()
	{
		return this->y;
	}
	
	void Object::setX(const int _x)
	{
		this->x = _x;
	}
	
	void Object::setY(const int _y)
	{
		this->y = _y;
	}
	
	Object& Object::reveal()
	{
		return *this;
	}
	
	void Object::show() const
	{
		std::cout << this->getSymbol();
	}
	
	void Object::encounterEvent(Alien& alien)
	{
		//std::cout << "Welcome to World Mr Alien " << alien.getSymbol() << std::endl;
	}
	
	void Object::setControl(Control* ptr)
	{
		this->control = ptr;
	}
	
	//StoryCharacter::StoryCharacter(): gameboard(*(new Gameboard()))
	//{
	//	
	//}
	
	StoryCharacter::StoryCharacter(Gameboard& board): gameboard(board), nextTranslationX(0), nextTranslationY(0)
	{
		
	}
	
	//StoryCharacter::~StoryCharacter()
	//{
	//	
	//}
	
	int StoryCharacter::getMaxLife() const
	{
		return this->maxLife;
	}
	
	void StoryCharacter::setMaxLife(const int _maxLife)
	{
		this->maxLife = _maxLife;
	}

	int StoryCharacter::getMaxAttackPower() const
	{
		return this->maxAttackPower;
	}
	
	void StoryCharacter::setMaxAttackPower(const int _maxAttackPower)
	{
		this->maxAttackPower = _maxAttackPower;
	}
	
	void StoryCharacter::move(const int x,const int y)
	{
		this->x = x;
		this->y = y;
	}

	void StoryCharacter::attack(StoryCharacter& storyCharacter)
	{
		
	}


	int StoryCharacter::attacked(const int damage)
	{
		int total = this->life;
		total -= total - damage;
		if(total<0)
			total = 0;
		this->life = total;
		return total;
	}

	void StoryCharacter::collect(const Health& health)
	{		
		
		
	}


	void StoryCharacter::collect(const Arrow& arrow)
	{
		
	}

	int StoryCharacter::getLife()
	{
		return this->life;
		
	}


	void StoryCharacter::setLife(const int life)
	{
		this->life = life;
		
	}

	int StoryCharacter::getAttackPower() 
	{
		return this->attackPower;
		
	}

	void StoryCharacter::setAttackPower(const int attackPower)
	{
		this->attackPower = attackPower;
		
	}
	
	void StoryCharacter::setNextTranslationX(int x)
	{
		this->nextTranslationX = x;
	}
	
	void StoryCharacter::setNextTranslationY(int y)
	{
		this->nextTranslationY = y;
	}
	
	int StoryCharacter::getNextTranslationX() const
	{
		return this->nextTranslationX;
	}
	
	int StoryCharacter::getNextTranslationY() const
	{
		return this->nextTranslationY;
	}
	
	
	
	//Alien::Alien()
	//{
	//	this->symbol = 'A';
	//}
	
	Alien::Alien(Gameboard& _gb):StoryCharacter(_gb),stopStatus(0)
	{
		this->symbol = 'A';
		this->maxLife = 100;
		this->life = maxLife;
		this->attackPower = 0;
		this->maxAttackPower = 100000000;
	}
	
	Alien::~Alien()
	{
		
	}
	
	void Alien::move(const int x, const int y)
	{
		int nextStepX = 0;
		int nextStepY = 0;
		const int lowerX = 0;
		const int upperX = this->gameboard.getColumnCount();
		const int upperY = 0;
		const int lowerY = this->gameboard.getRowCount();
		int nextX = 0;
		int nextY = 0;
		int x1 = 0;
		int y1 = 0;
		int cacheX = 0;
		int cacheY = 0;
		this->setNextTranslationX(x - this->getX());
		this->setNextTranslationY(y - this->getY());
		
		while(this->isReadyToMove()&&((this->getNextTranslationX()!=0)||((this->getNextTranslationY()!=0))))
		{
			nextStepX = 0;
			nextStepY = 0;
			cacheX = this->getNextTranslationX();
			cacheY = this->getNextTranslationY();
			nextStepX = this->calculateNextStep(cacheX);
			nextStepY = this->calculateNextStep(cacheY);
			
			nextX = this->getX()+nextStepX;
			nextY = this->getY()+nextStepY;
			if((nextX>=lowerX)&&(nextX<upperX)&&(nextY>=upperY)&&(nextY<lowerY))
			{
				Object& encounterObj = this->gameboard.getObjectAt(nextX, nextY);
				Object& trObj = this->yields();
				encounterObj.encounterEvent(*this);
				//if(this->control!=nullptr)
				//{
				//	this->control->display();
				//	pf::Pause();
				//}
				if(this->isReadyToMove())
				{					
					x1 = this->getX();
					y1 = this->getY();
					this->gameboard.placeAlien(*this,nextX,nextY);
					if(cacheX==this->getNextTranslationX())
						this->setNextTranslationX(this->getNextTranslationX()-nextStepX);
					if(cacheY==this->getNextTranslationY())
						this->setNextTranslationY(this->getNextTranslationY()-nextStepY);
					this->gameboard.setObjectAt(trObj,x1,y1);
					
				}
				else
				{
					this->setNextTranslationX(0);
					this->setNextTranslationY(0);
				}
				
				
			}
			else
			{
				this->stop();
			}
			
			if(this->control!=nullptr)
			{
				this->control->display();
				pf::Pause();
				
			}
		}
	}
	
	int Alien::calculateNextStep(const int nextTranslation)
	{
		int nextStep = 0;
		if(nextTranslation>0)
		{
			nextStep = 1;
		}
		else
		{
			if(nextTranslation<0)
			{
				nextStep = -1;
			}
			
		}
		return nextStep;
	}
	
	void Alien::attack(StoryCharacter& enemy)
	{
		std::cout << "alien attacks storyCharacter enemy" << std::endl;
	}
	
	void Alien::attack(Zombie& enemy)
	{
		int x = 0;
		int y = 0;
		Object* ptr = nullptr;
		std::stringstream ss;
		int level = enemy.getLife() ;
		int damage = level - this->getAttackPower();
		//std::cout << "alien attacks Zombie enemy" << std::endl;
		ss << "(Zombie " << enemy.getSymbol() << " Life) "<< level << " - (Alien Attack Power!) " << this->getAttackPower() << " = ";
		ss	<< " (Zombie " << enemy.getSymbol() << " After Attacked)" << damage << std::endl;
		enemy.setLife(damage);
		this->setAttackPower(0);
		if(enemy.getLife()<=0)
		{
			ss << "Zombie " << enemy.getSymbol() << " Terminated " << std::endl;
			x = enemy.getX();
			y = enemy.getY();
			enemy.setX(-1);
			enemy.setY(-1);
			ptr = new Space();
			this->gameboard.setObjectAt(*ptr, x, y);
			
		}
		else
		{
			this->setNextTranslationX(0);
			this->setNextTranslationY(0);
			this->stop();
			ss << "Zombie " << enemy.getSymbol() << " Survived with Life " << enemy.getLife() << "!!! Zombie "<< enemy.getSymbol() << " ->Alien: Prepared for Worst!!!" << std::endl;
			ss << "Alien Stopped at x = " << this->getX() << ", y = " << this->getY() << std::endl;
		}
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
			//this->control->display();
		}
	}
	
	Object& Alien::yields()
	{
		Object* ptr = new Trail();
		ptr->setControl(this->control);
		return *ptr;
	}
	
	bool Alien::isReadyToMove()
	{
		return ((this->stopStatus)==0);
	}
	
	void Alien::stop()
	{
		this->stopStatus = 1;
		
	}
	
	void Alien::readyToGo()
	{
		this->stopStatus = 0;
	}
	
	void Alien::collect(const Arrow& arrow)
	{
		int additional = arrow.getAttackPower();
		std::stringstream ss;
		ss << "(Alien Attack) " << this->attackPower << " + (Attack Power) " << additional << " = ";
		this->attackPower += arrow.getAttackPower();
		ss << " (Total Attack)"<< this->attackPower  << std::endl;
		
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
			//this->control->display();
		}
		
	}
	
	void Alien::collect(const Health& health)
	{		
		int level = this->life;
		int additional = health.getHealingPoint();
		int total = level + additional;
		std::stringstream ss;
		if(total > this->maxLife)
		{	
			
			ss <<"(Alien) " << level << " + (Health) " << additional << " = (Total Life) " << total  << std::endl;
			total = this->maxLife;
			ss << "\tFull=>\tOverflow=>\tTotal=>" << total;
		}
		else
		{
			ss <<"(Alien) " << level << " + (Health) " << additional << " = (Total Life) " << total  << std::endl;
		}
		this->life = total;
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
			//this->control->display();
		}
	}
	
	
	void Alien::collect(Rock& rock)
	{
		std::stringstream ss;
		std::cout << "^^^^^^^^Alien discovered Object Under Rock" << std::endl;
		ss << "Alien discovered Object Under Rock" << std::endl;
		Object& obj = rock.reveal();
		this->gameboard.setObjectAt(obj,rock.getX(), rock.getY());
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
			//this->control->display();
		}
		
	}
	
	//Zombie::Zombie()
	//{
	//	std::cout << "zombie wakes up" << std::endl;
	//	this->symbol= '1';
	//}
	
	Zombie::Zombie(Gameboard& gb):StoryCharacter(gb),attackRange(0)
	{
		this->symbol= '1';
		this->setMaxAttackPower(150);
		this->setMaxLife(500);
		
	}
	
	Zombie::Zombie(Gameboard& gb, const char ch):StoryCharacter(gb), attackRange(1)
	{
		this->symbol = ch;
		this->setMaxAttackPower(100);
		this->setMaxLife(250);
	}
	
	//Zombie::Zombie(Gameboard& gb, const int attack_range, const char ch):StoryCharacter(gb), attackRange(attack_range)
	Zombie::Zombie(Gameboard& gb, const char ch, const int _life, const int attack_power, const int attack_range)
		:StoryCharacter(gb),  attackRange(attack_range)
	{
		this->symbol = ch;
		this->life = _life;
		this->attackPower = attack_power;
	}
	
	//Zombie::~Zombie()
	//{
	//	
	//}
	
	
	
	int Zombie::getAttackRange() const
	{
		return this->attackRange;
	}
	
	void Zombie::setAttackRange(const int _attackRange)
	{
		this->attackRange = _attackRange;
	}
		
	void Zombie::encounterEvent(Alien& alien)
	{
		//std::cout << "Zombie encounterEvent " << std::endl;
		std::stringstream ss;
		ss << "Alien Confronts with Zombie " << this->getSymbol() <<" at x = " << this->getX()+1 << ", y = " << this->getY()+1 << std::endl;
		if(this->control!=nullptr)
		{
			this->control->setStatusTxt(ss.str());
			//this->control->display();
		}
		alien.stop();
		alien.attack(*this);
	}
		
	Health::Health():healingPoint(20)
	{
		this->symbol = 'h';
		
	}
	
	Health::Health(const int point) : healingPoint(point)
	{
		this->symbol = 'h';
		
	}
	
	//Health::~Health()
	//{
	//	std::cout << "~~~health "<< std::endl;
	//}
	
	int Health::getHealingPoint() const
	{
		return this->healingPoint;
	}
	
	void Health::encounterEvent(Alien& alien)
	{
		std::stringstream ss;
		ss << "Alien Collects to Health at x = " << this->getX()+1 << ", y = " << this->getY()+1 <<  ". Health capacity = " << this->getHealingPoint() <<std::endl;
		
		if(this->control!=nullptr)
		{
			this->control->setStatusTxt(ss.str());
			//this->control->display();
		}
		
		alien.collect(*this);
		//std::cout << "Health encounterEvent" << std::endl;
	}
	
	Arrow::Arrow():attackPower(20)
	{
		this->symbol = '>';
	}
	
		
	Arrow::Arrow(const int _aPower, const char _symbol):attackPower(_aPower)
	{
		this->symbol=_symbol;
		
	}
	 
	Arrow::Arrow(Arrow& _arrow):attackPower(_arrow.attackPower)
	{
		this->symbol = _arrow.getSymbol();
	}
	
	//Arrow::~Arrow()
	//{
	//	std::cout<< "arrow ~~" << std::endl;
	//}
	
	void Arrow::encounterEvent(Alien& alien)
	{
		char ch = 0;
		//std::cout << "Arrow encounterEvent" << std::endl;
		std::stringstream ss;
		ss << "Alien Collects to Arrow " << this->getSymbol() << " at x = " << this->getX()+1 << ", y = " << this->getY()+1 <<  ". Arrow Power = " << this->getAttackPower() <<std::endl;
		
		if(this->control!=nullptr)
		{
			this->control->setStatusTxt(ss.str());
			//this->control->display();
		}
		
		
		alien.collect(*this);
		ch = this->getSymbol();
		switch(ch)
		{
			case '^':
				alien.setNextTranslationX(0);
				alien.setNextTranslationY(-(alien.getY()));
			break;
			
			case 'v':
				alien.setNextTranslationX(0);
				alien.setNextTranslationY(999);
			break;
			
			case '<':
				alien.setNextTranslationX(-(alien.getX()));
				alien.setNextTranslationY(0);
			break;
			
			case '>':
				alien.setNextTranslationX(999);
				alien.setNextTranslationY(0);
			break;
						
		}
		alien.readyToGo();
	}
	
	
	int Arrow::getAttackPower() const
	{
		return this->attackPower;
	}
	
	Rock::Rock(): flipped(false)
	{
		this->symbol = 'r';
		
		
	}
	
	//Rock::~Rock()
	//{
	//	
	//}
	
	void Rock::encounterEvent(Alien& alien)
	{
		std::stringstream ss;
		ss << "Alien blocked by Rock" << std::endl; 
		ss << "Alien location x = " << alien.getX()+1 << ", y = " << alien.getY()+1 <<  std::endl;
		ss << "Rock location x = " << this->getX()+1 << ", y = " << this->getY()+1 <<  std::endl;
		//std::cout << "rock encounterEvent" << std::endl;
		//std::cout << "alien stop" << std::endl;
		alien.setNextTranslationX(0);
		alien.setNextTranslationY(0);
		alien.stop();
		this->flipped = true;
		//alien.collect(*this);
		if(this->control!=nullptr)
		{
			this->control->setStatusTxt(ss.str());
			//this->control->display();
		}
	}
	
	Object& Rock::reveal()
	{
		Object* ptr = this;
		if(this->flipped)
		{
			Object& obj = this->discovered();
			ptr = &obj;
			ptr->setControl(this->control);
			this->flipped = false;
			
		}
		return *ptr;
	}
	
	Object& Rock::discovered()
	{
		Object* ptr = nullptr;
		std::stringstream ss;
		int randomNumber = std::rand()%7;
		char ch = 0;
		const int attackPower = 10;
		const int healingPoint = 20;
		switch(randomNumber)
		{
			case 0:
				ch = '<';
				ptr = new Arrow(attackPower, ch);
			break;
			case 1:
				ch = '>';
				ptr = new Arrow(attackPower, ch);
			break;
			case 2:
				ch = '^';
				ptr = new Arrow(attackPower, ch);
			break;
			case 3:
				ch = 'v';
				ptr = new Arrow(attackPower, ch);
			break;
			case 4:
				ch = 'h';
				ptr = new Health(healingPoint);
			break;
			
			case 5:
				ch = (char)32;
				ptr = new Space();
			break;
			case 6:
				ch = 'p';
				ptr = new Pod();
			break;
			//case 8:
			//	ch = '.';
			//	object.push_back(new Trail());
			//break;
			
		}
		ss << "Rock x = "<< this->getX()+1 << ", y = " << this->getY()+1  << " =>  (" << ch << ")" << std::endl;
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
		}
		return *ptr;
	}
			
	Space::Space()
	{
		this->symbol = 32;
		
	}
	
	//Space::~Space()
	//{
	//	
	//}
	
	void Space::encounterEvent(Alien& alien)
	{
		//std::cout << "Space encounterEvent" << std::endl;
		std::stringstream ss;
		ss << "Alien traveled to SPACE at x = " << this->getX()+1 << ", y = " << this->getY()+1 << std::endl;
		if(this->control!=nullptr)
		{
			this->control->setStatusTxt(ss.str());
			//this->control->display();
		}
	}
	
	Pod::Pod()
	{
		this->symbol = 'p';
		
	}
	
	//Pod::~Pod()
	//{
	//	
	//}
	
	void Pod::encounterEvent(Alien& alien)
	{
		//std::cout << "Pod encounterEvent" << std::endl;
		std::stringstream ss;
		ss << "Alien traveled to Pod at x = " << this->getX()+1 << ", y = " << this->getY()+1 << std::endl;
		if(this->control!=nullptr)
		{
			this->control->setStatusTxt(ss.str());
			//this->control->display();
		}
	}
	
	Trail::Trail()
	{
		this->symbol = '.';
		
	}
	
	Object& Trail::reveal()
	{
		Object* ptr = nullptr;
		int randomNumber = std::rand()%8;
		char ch = 0;
		const int attackPower = 10;
		const int healingPoint = 20;
		std::stringstream ss;
		
		switch(randomNumber)
		{
			case 0:
				ch = '<';
				ptr = new Arrow(attackPower, ch);
			break;
			case 1:
				ch = '>';
				ptr = new Arrow(attackPower, ch);
			break;
			case 2:
				ch = '^';
				ptr = new Arrow(attackPower, ch);
			break;
			case 3:
				ch = 'v';
				ptr = new Arrow(attackPower, ch);
			break;
			case 4:
				ch = 'h';
				ptr = new Health(healingPoint);
			break;
			case 5:
				ch = 'r';
				ptr = new Rock();
			break;
			case 6:
				ch = (char)32;
				ptr = new Space();
			break;
			case 7:
				ch = 'p';
				ptr = new Pod();
			break;
			//case 8:
			//	ch = '.';
			//	object.push_back(new Trail());
			//break;
			
		}
		
		if(ptr!=nullptr)
		{
			ptr->setControl(this->control);
		}
		
		ss << "Trail at x = " << this->getX() << ", y = " << this->getY() << " => (" << ch << ")" <<std::endl;
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
			//this->control->display();
		}
		return *ptr;
	}
	
	//Trail::~Trail()
	//{
	//	
	//}
	
	void Trail::encounterEvent(Alien& alien)
	{
		//std::cout << "Trail encounterEvent" << std::endl;
		std::stringstream ss;
		ss << "Alien traveled to Trail at x = " << this->getX()+1 << ", y = " << this->getY()+1 << std::endl;
		if(this->control!=nullptr)
		{
			this->control->setStatusTxt(ss.str());
			//this->control->display();
		}
		
	}
	
	Control::Control(Gameboard& gb, Alien& al):gameboard(gb), alien(al),commandTxt(),statusTxt(),statusCode(0),turnCount(0)
	{
		this->gameboard.setControl(this);
		this->alien.setControl(this);
	}
	
	Control::~Control()
	{
		
	}
	
	void Control::display()
	{
		//pf::ClearScreen();
		this->gameboard.show();
		this->displayStoryCharacterStatus();
		this->displayStatusTxt();
		//pf::Pause();
		this->statusTxt.clear();
	}
	
	void Control::displayStoryCharacterStatus()
	{
		int i = 0;
		int j = 0;
		
		std::cout << std::endl << ((this->turnCount==0)?'*':' ') << "Alien";
		for(i=0; i < 5; ++i)
		{
			std::cout << ' ';
		}
		std::cout << ':';
		for(i=0; i < 4; ++i)
		{
			std::cout << ' ';
		}
		std::cout <<"Life "<< this->alien.getLife() <<", Attack " << this->alien.getAttackPower() ;
		for(i=0; i < 18 ; ++i)
		{
			std::cout << ' ';
		}
		std::cout << "x " << this->alien.getX()+1 << ", y " << this->alien.getY()+1 << std::endl;
		for(j=0; j < this->gameboard.getZombieCount(); ++j)
		{
			
			Zombie& zombie = this->gameboard.getZombie(j);
			std::cout << std::endl << ((this->turnCount==(j+1))?'*':' ');
			std::cout << "Zombie " << zombie.getSymbol() << "  :    Life " << zombie.getLife() << ", Attack " << zombie.getAttackPower() ;
			std::cout << ", Range " << zombie.getAttackRange() << std::endl;
			
		}
		
	}
	
	void Control::requestInput()
	{
		std::cout << std::endl << "command:";
		std::cin >> this->commandTxt;
		std::cout << std::endl;
	}
	
	char tolower(char _ch)
	{
		return std::tolower(_ch);
	}
	
	void Control::processInput()
	{
		
		//std::transform(this->commandTxt.begin(), this->commandTxt.end(),this->commandTxt.begin(), &(std::tolower));
		std::transform(this->commandTxt.begin(), this->commandTxt.end(),this->commandTxt.begin(), tolower);
		//char ch = std::tolower('K');
		std::cout << "Command was: "<< this->commandTxt << std::endl;
		if(this->commandTxt=="up")
		{
			this->processCommandUp();
		}
		else
		{
			if(this->commandTxt=="quit")
			{
				this->statusCode = 1;
				
			}
			else
			{
				if(this->commandTxt=="down")
				{
					this->processCommandDown();
				}
				else
				{
					if(this->commandTxt=="left")
					{
						this->processCommandLeft();
					}
					else
					{
						if(this->commandTxt=="right")
						{
							this->processCommandRight();
						}
						else
						{
							if(this->commandTxt=="arrow")
							{
								this->processCommandArrow();
							}
							else
							{
								if(this->commandTxt=="help")
								{
									this->processCommandHelp();
								}
								else
								{
									if(this->commandTxt=="save")
									{
										this->processCommandSave();
									}
									else
									{
										if(this->commandTxt=="load")
										{
											this->processCommandLoad();
										}
									}
								}
							}
						}
					}
				}
			}
			
		}
		
	}
	
	void Control::processCommandUp()
	{
		//this->alien.setNextTranslationY(-(this->alien.getY()));
		this->alien.setNextTranslationX(0);
		this->alien.setNextTranslationY(-(this->alien.getY()));
		this->alien.readyToGo();
		this->alien.move(this->alien.getX(),0);
		
		this->gameboard.refreshAllTrail();
	}
	
	
	
	void Control::_processCommandUp()
	{
		int x = this->alien.getX();
		int y = this->alien.getY();
		Object& obj = this->alien.yields();
		for(; this->alien.isReadyToMove();--y)
		{
			if((y-1)>=0)
			{
				Object& encounterObj = this->gameboard.getObjectAt(x,y-1);
				std::cout << "encounterObject.show()=>";
				encounterObj.show();
				
				encounterObj.encounterEvent(this->alien);
				
				std::cout << std::endl;
				if(this->alien.isReadyToMove())
				{
					this->gameboard.placeAlien(this->alien,x,y-1);
					this->gameboard.setObjectAt(obj,x,y);
				}
				else
				{
					Object& revealObj = encounterObj.reveal();
					if((&revealObj)!=(&encounterObj))
					{
						this->gameboard.setObjectAt(revealObj,x,y);
						delete &encounterObj;
					}
				}
				
			}
			else
			{
				this->alien.stop();
			}
			pf::Pause();
		}
		
	}
	
	void Control::processCommandDown()
	{
		this->alien.setNextTranslationX(0);
		this->alien.setNextTranslationY(999);
		this->alien.readyToGo();
		this->alien.move(this->alien.getX(),999);
		this->gameboard.refreshAllTrail();
	}
	
	
	void Control::processCommandLeft()
	{
		this->alien.setNextTranslationX(-(this->alien.getX()));
		this->alien.setNextTranslationY(0);
		this->alien.readyToGo();
		this->alien.move(0,this->alien.getY());
		this->gameboard.refreshAllTrail();
	}
	
	void Control::processCommandRight()
	{
		this->alien.setNextTranslationX(999);
		this->alien.setNextTranslationY(0);
		this->alien.readyToGo();
		this->alien.move(999,this->alien.getY());
		this->gameboard.refreshAllTrail();
	}
	
	void Control::processCommandArrow()
	{
		
	}
	
	void Control::processCommandHelp()
	{
		std::cout<<"1.up	-Move up."<<std::endl;
		std::cout<<"2.down	-Move down."<<std::endl;
		std::cout<<"3.left	-Move left."<<std::endl;
		std::cout<<"4.right	-Move right."<<std::endl;
		std::cout<<"5.arrow	-Change arrow direction."<<std::endl;
		std::cout<<"6.help	-Display these user commands."<<std::endl;
		std::cout<<"7.save	-Save the game."<<std::endl;
		std::cout<<"8.load	-Load a game."<<std::endl;
		std::cout<<"9.quit	-Quit the game."<<std::endl;
		
	}
	
	void Control::processCommandSave()
	{
		
	}
	
	void Control::processCommandLoad()
	{
		
	}
	
	int Control::work()
	{
		while(this->statusCode==0)
		{	
			this->display();
			this->requestInput();
			this->processInput();
			
		}
		std::cout << "Status Code == " << this->statusCode << std::endl;
		
		return this->statusCode;
	}
	
	void Control::setStatusTxt(const char* txt)
	{
		this->statusTxt = std::string(txt);
	}
	
	void Control::setStatusTxt(const std::string& txt)
	{
		this->statusTxt = txt;
	}
	
	void Control::addStatusTxt(const char* txt)
	{
		this->statusTxt += std::string(txt);
	}
	
	void Control::addStatusTxt(const std::string& txt)
	{
		this->statusTxt += txt;
	}
	
	void Control::displayStatusTxt() const
	{
		std::cout << this->statusTxt << std::endl;
	}

	
}