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
	#include "AVZ.hpp"

namespace avz
{
	Gameboard::Gameboard():rowCount(3),columnCount(19), zombieCount(3), objects(rowCount), zombies(0), control(nullptr)//, map(nullptr)
	{
		
		Gameboard(rowCount,columnCount);
	}
	
	Gameboard::Gameboard(const int row, const int column): rowCount(row),columnCount(column) ,zombieCount(3), objects(row),zombies(0), control(nullptr)//, map(nullptr), 
	{
		std::cout << "Gameboard" << std::endl;
		
		//std::srand(time(0));
		
		this->randFill();
		this->randFillZombie();
		
	}
	
	Gameboard::Gameboard(const int row, const int column, int zbCount): rowCount(row),columnCount(column) ,zombieCount(zbCount), objects(row),zombies(0), control(nullptr)//, map(nullptr), 
	{
		std::cout << "Gameboard" << std::endl;
		
		std::srand(time(0));
		this->randFill();
		this->randFillZombie();
	}

	
	
	Gameboard::~Gameboard()
	{
		Object* ptr = nullptr;
		this->zombies.clear();
		
		for(std::list<std::list<Object*> >::iterator it = this->objects.begin(); it != this->objects.end();)
		{
			for(std::list<Object*>::iterator inner_it = it->begin(); inner_it!= it->end();)
			{
				ptr = *inner_it;
				inner_it = it->erase(inner_it);
				if((this->control!=nullptr)&&(ptr!=(&(this->control->getAlien()))))
				{
					delete ptr;
				}
				
			}
			it = this->objects.erase(it);
		}
		
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
		std::cout.flush();
	}
	
	void Gameboard::randFill()
	{
		Object* ptr = nullptr;
		Pod* podPtr = nullptr;
		int i = 0;
		int j = 0;
		int randomNumber = 0;
		char ch = 0;
		const int attackPower = 20;
		const int healingPoint = 20;
		int randomRange = 0;
		int smaller = 0;
		
		std::srand(time(0));
		std::cout << "row=" << this->rowCount << ",columnCount=" << this->columnCount << std::endl;
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
						podPtr = new Pod();
						ptr = podPtr;
						//object.push_back(new Pod());
					break;
					//case 8:
					//	ch = '.';
					//	object.push_back(new Trail());
					//break;
					
				}
				if(ptr!=nullptr)
				{
					if(podPtr!=nullptr)
					{
						smaller = this->getRowCount();
						if(this->getColumnCount()<smaller)
							smaller = this->getColumnCount();
						do
						{
							randomRange  = std::rand()%smaller;
						
						}while(randomRange==0);
						podPtr->setAttackRange(randomRange);
						podPtr = nullptr;
					}
					
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
		std::srand(time(0));
		//std::cout << "zombieCount = " << this->getZombieCount() << std::endl;
		//for(i=0; i < this->getZombieCount(); ++i)
		for(i=0; i < this->zombieCount; ++i)
		{
			do
			{
				random_x = std::rand()%this->columnCount;
				random_y = std::rand()%this->rowCount;
			}while(((random_x==this->columnCount/2)&&(random_y==this->rowCount/2))||(this->isZombie(random_x,random_y)));
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
							if(((char)(i+49))< 'A')
								ptr = new Zombie(*this,(char) (i+49));
							else
								ptr = new Zombie(*this, (char) (i+49+1));
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
							*inner_it = ptr;
							pending = false;
						}
						++x;
					}
				}
				++y;
				
			}
		}
	}
	
	bool Gameboard::isZombie(const int x, const int y) const
	{
		bool result = false;
		for(std::list< Zombie*>::const_iterator cit = this->zombies.begin(); (result==false)&&(cit!=this->zombies.end());cit++)
		{
			Zombie* zombie = *cit;
			if(zombie!=nullptr)
			{
				result = ((zombie->getX()==x)&&(zombie->getY()==y));
			}
		}
		
		return result;
		
	}
	
	bool Gameboard::isArrow(const int x, const int y) 
	{
		bool result = false;
		char ch = 0;
		Object obj = this->getObjectAt(x,y);
		ch = obj.getSymbol();
		result = (ch=='<')||(ch=='^')||(ch=='>')||(ch=='v');
		
		return result;
		
	}
	
	void Gameboard::fill()
	{
		this->objects.resize(this->rowCount);
		for( std::list<std::list<Object*> >::iterator it = this->objects.begin(); it!=this->objects.end(); it++)
		{
			std::list<Object*>& object = *it;
			object.resize(this->columnCount);
		}
	}
	
	void Gameboard::fillZombies()
	{
		this->zombies.resize(this->zombieCount);
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
		int i = 0;
		int j = 0;
		for(std::list< std::list<Object*> >::iterator it = this->objects.begin(); it!=this->objects.end(); it++ )
		{
			i = 0;
			for(std::list<Object*>::iterator inner_it = (*it).begin(); inner_it!=(*it).end(); inner_it++)
			{
				Object& obj = (*inner_it)->reveal();
				Object* pt = *inner_it;
				if((&obj)!=(*inner_it))
				{
					*inner_it = &obj;
					(*inner_it)->setX(i);
					(*inner_it)->setY(j);
					delete pt;
				}
				++i;				
			}
			++j;
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
		int count = 0;
		count = this->zombies.size();
		//return this->zombieCount;
		return count;
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
	
	void Gameboard::alienMove(int direction)
	{
		int next = -1;
		bool check = false;
		Object* obj = nullptr;
		int x = -1;
		int y = -1;
		int previousX = -1;
		int previousY = -1;
		Object* obj1 = nullptr;
		int _nextDirection = direction;
		
		if(this->control!=nullptr)
		{
			this->control->getAlien().setMovement(_nextDirection);
			while((_nextDirection=this->control->getAlien().getMovement())!=0)
			{
				check = false;
				next = this->control->getAlien().move();
				
				if(next>=0)
				{
					switch(_nextDirection)
					{
						//right or left
						case 1:
						case 3:
							check = this->withinBoard(next,0);
							x = next;
							y = this->control->getAlien().getY();
						break;
						
						//down or up
						case 2:
						case 4:
							check = this->withinBoard(next,1);
							y = next;
							x = this->control->getAlien().getX();
						break;
						
					}
					
				}
				std::cout << "next=" << next << ",check=" << check << std::endl;
				if(check==false)
				{	
					//alien stop. hits border
					this->control->getAlien().setMovement(0);
			
				}
				else
				{
					obj = &(this->getObjectAt(x,y));
					this->encounter(&(this->control->getAlien()), obj);
					if(this->control->getAlien().getMovement()!=0)
					{
						previousX = this->control->getAlien().getX();
						previousY = this->control->getAlien().getY();
						obj1 = &(this->control->getAlien().yields());
												
						this->control->getAlien().setX(x);
						this->control->getAlien().setY(y);
						this->setObjectAt(this->control->getAlien(), x, y);
						
						obj1->setX(previousX);
						obj1->setY(previousY);
						this->setObjectAt(*obj1,previousX,previousY);
						
						
					}
					if(this->control!=nullptr)
					{
						this->control->display();
						pf::Pause();
						
					}
				}
				
			}
		}
		
	}
	
	
	void Gameboard::zombieMove(Zombie* zombie, int direction)
	{
		int next = -1;
		bool check = false;
		Object* obj = nullptr;
		int x = -1;
		int y = -1;
		int previousX = -1;
		int previousY = -1;
		int nextX = -1;
		int nextY = -1;
		
		Object* obj1 = nullptr;
		int _nextDirection = direction;
		
		if((this->control!=nullptr)&&(zombie!=nullptr)&&(zombie->getX()>=0)&&(zombie->getY()>=0))
		{
			
			
			zombie->setMovement(_nextDirection);
			if((_nextDirection=zombie->getMovement())!=0)
			{
				check = false;
				next = zombie->move();
				std::cout << "zombie move next=" << next << std::endl;
				if(next>=0)
				{
					switch(_nextDirection)
					{
						//right or left
						case 1:
						case 3:
							check = this->withinBoard(next,0);
							x = next;
							y = zombie->getY();
						break;
						
						//down or up
						case 2:
						case 4:
							check = this->withinBoard(next,1);
							y = next;
							x = zombie->getX();
						break;
						
					}
					
				}
				if(check==false)
				{	
					//alien stop. hits border
					zombie->setMovement(0);
			
				}
				else
				{
					obj = &(this->getObjectAt(x,y));
					this->encounter(zombie, obj);
					if(zombie->getMovement()!=0)
					{
						previousX = zombie->getX();
						previousY = zombie->getY();
						obj1 = &(zombie->yields());
												
						zombie->setX(x);
						zombie->setY(y);
						this->setObjectAt(*zombie, x, y);
						
						obj1->setX(previousX);
						obj1->setY(previousY);
						this->setObjectAt(*obj1,previousX,previousY);
						
						Alien& alien = this->control->getAlien();
						nextX = alien.getX() - x;
						nextY = alien.getY() - y;
						nextX = ((nextX>=0)? nextX:-nextX);
						nextY = ((nextY>=0)? nextY:-nextY);
						if((nextX<=zombie->getAttackRange())&&(nextY<=zombie->getAttackRange()))
						{
							zombie->attack(&alien);
							
						}
						
						
					}
					if(this->control!=nullptr)
					{
						this->control->display();
						pf::Pause();
						
					}
				}
				
			}
			
		}
		
	}
	
	bool Gameboard::withinBoard(int location, int axis) const
	{
		bool result = false;
		if(location>=0)
		{
			if(axis==0)	//x axis
			{
				result = ((this->columnCount)> location);
			}
			else
			{
				// y axis
				result = ((this->rowCount)> location);
			}
		}
		return result;
	}
	
	void Gameboard::encounter(Alien* alien, Object* object)
	{
		char ch = 0;
		std::stringstream ss;
		Zombie* zombie = nullptr;
		Arrow* arrow = nullptr;
		Rock* rock = nullptr;
		Health* health = nullptr;
		Space* space = nullptr;
		Pod* pod = nullptr;
		Trail* trail = nullptr;
		int x = 0;
		int y = 0;
		if((alien!=nullptr)&&(object!=nullptr))
		{
			ch = object->getSymbol();
			std::cout <<"encounter ch="<< ch << std::endl;
			switch(ch)
			{
				//zombie
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					zombie = (Zombie*) object;
					ss << "Alien Confronts with Zombie " << ch <<" at x = " << alien->getX()+1 << ", y = " << alien->getY()+1 << std::endl;
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
					alien->attack(*zombie);
				break;
				
				
				//arrow
				case '>':
					arrow = (Arrow*) object;
					ss << "Alien Collects to Arrow " << ch << " at x = " << arrow->getX()+1 << ", y = " << arrow->getY()+1 <<  ". Arrow Power = " << arrow->getAttackPower() <<std::endl;
		
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
					alien->collect(*arrow);
					alien->setMovement(1);				
				break;
			
				case 'v':
					arrow = (Arrow*) object;
					ss << "Alien Collects to Arrow " << ch << " at x = " << arrow->getX()+1 << ", y = " << arrow->getY()+1 <<  ". Arrow Power = " << arrow->getAttackPower() <<std::endl;
		
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
					alien->collect(*arrow);
					alien->setMovement(2);			
				break;
			
				case '<':
					arrow = (Arrow*) object;
					ss << "Alien Collects to Arrow " << ch << " at x = " << arrow->getX()+1 << ", y = " << arrow->getY()+1 <<  ". Arrow Power = " << arrow->getAttackPower() <<std::endl;
		
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
					alien->collect(*arrow);
					alien->setMovement(3);			
				break;
						
		
				case '^':
					arrow = (Arrow*) object;
					ss << "Alien Collects to Arrow " << ch << " at x = " << arrow->getX()+1 << ", y = " << arrow->getY()+1 <<  ". Arrow Power = " << arrow->getAttackPower() <<std::endl;
		
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
					alien->collect(*arrow);
					alien->setMovement(4);			
				break;
				
				
				//rock
				case 'r':
					rock = (Rock*) object;
					ss << "Alien blocked by Rock" << std::endl; 
					ss << "Alien location x = " << alien->getX()+1 << ", y = " << alien->getY()+1 <<  std::endl;
					ss << "Rock location x = " << rock->getX()+1 << ", y = " << rock->getY()+1 <<  std::endl;
					alien->setMovement(0);	//alien stop
					//rock->flipped = true;
					rock->flip();
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
				break;
				
				//health
				case 'h':
					health = (Health*) object;
					ss << "Alien Collects to Health at x = " << alien->getX()+1 << ", y = " << alien->getY()+1 <<  ". Health capacity = " << health->getHealingPoint() <<std::endl;
		
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
					alien->collect(*health);
				break;
				
				//space
				case ' ':
					space = (Space*) object;
					ss << "Alien traveled to SPACE at x = " << space->getX()+1 << ", y = " << space->getY()+1 << std::endl;
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
				break;
				
				//pod
				case 'p':
					pod = (Pod*) object;
					x = pod->getX();
					y = pod->getY();
					ss << "Alien traveled to Pod at x = " << x+1 << ", y = " << y+1 << ". Effective Power = " << pod->getAttackPower() <<  ". Effective Range = " << pod->getAttackRange() << std::endl;
					alien->collect(*pod);
					
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
				break;
				
				//Trail
				case '.':
				trail = (Trail*) object;
					ss << "Alien traveled to Trail at x = " << trail->getX()+1 << ", y = " << trail->getY()+1 << std::endl;
					if(this->control!=nullptr)
					{
						this->control->setStatusTxt(ss.str());
						//this->control->display();
					}
				break;
			}
			
		}
	}
	
	void Gameboard::encounter(Zombie* zombie, Object* object)
	{
		char ch = 0;
		std::stringstream ss;
		//Zombie* zombie1 = nullptr;
		Arrow* arrow = nullptr;
		Rock* rock = nullptr;
		Health* health = nullptr;
		Space* space = nullptr;
		Pod* pod = nullptr;
		Trail* trail = nullptr;
		Zombie* zombie1 = nullptr;
		int x = 0;
		int y = 0;
		
		if((object!=nullptr)&&(zombie!=nullptr))
		{
			ch = object->getSymbol();
			switch(ch)
			{
				//zombie
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				zombie1 = (Zombie*) object;
				ss << "Zombie "<< zombie->getSymbol() <<" meets with Zombie " << zombie1->getSymbol() <<" at x = " << zombie1->getX()+1 << ", y = " << zombie1->getY()+1 << std::endl;
				if(this->control!=nullptr)
				{
					this->control->setStatusTxt(ss.str());
					//this->control->display();
				}
				zombie->setMovement(0);
							
				break;
				
				//arrow
				case '<':
				case '^':
				case '>':
				case 'v':
					arrow = (Arrow*) object;
					x = zombie->getX() - arrow->getX();
					y = zombie->getY() - arrow->getY();
					if((((x==-1)||(x==1))&&(y==0))||(((y==-1)||(y==1))&&(x==0)))
					{
						ss << "Zombie " << zombie->getSymbol() << " walks to Arrow " << ch << " at x = " << arrow->getX()+1 << ", y = " << arrow->getY()+1 <<  ". Arrow Power = " << arrow->getAttackPower() << std::endl;
												
						if(this->control!=nullptr)
						{
							this->control->setStatusTxt(ss.str());
							//this->control->display();
						}
					}
				
				break;
				
				//rock
				case 'r':
					rock = (Rock*) object;
					x = zombie->getX() - rock->getX();
					y = zombie->getY() - rock->getY();
					if((((x==-1)||(x==1))&&(y==0))||(((y==-1)||(y==1))&&(x==0)))
					{
						ss << "Zombie " << zombie->getSymbol() << " walks to Rock at x = " << rock->getX()+1 << ", y = " << rock->getY()+1 << std::endl;
						
						if(this->control!=nullptr)
						{
							this->control->setStatusTxt(ss.str());
							//this->control->display();
						}
					}
				break;
				
				//health
				case 'h':
					health = (Health*) object;
					x = zombie->getX() - health->getX();
					y = zombie->getY() - health->getY();
					if((((x==-1)||(x==1))&&(y==0))||(((y==-1)||(y==1))&&(x==0)))
					{
						ss << "Zombie " << zombie->getSymbol() << " walks to Health at x = " << health->getX()+1 << ", y = " << health->getY()+1 <<  ". Health capacity = " << health->getHealingPoint() <<std::endl;
					
						if(this->control!=nullptr)
						{
							this->control->setStatusTxt(ss.str());
							//this->control->display();
						}
					}
				break;
				
				//space
				case ' ':
					space = (Space*) object;
					x = zombie->getX() - space->getX();
					y = zombie->getY() - space->getY();
					if((((x==-1)||(x==1))&&(y==0))||(((y==-1)||(y==1))&&(x==0)))
					{
						ss << "Zombie " << zombie->getSymbol() << " traveled to SPACE at x = " << space->getX()+1 << ", y = " << space->getY()+1 << std::endl;
						if(this->control!=nullptr)
						{
							this->control->setStatusTxt(ss.str());
							//this->control->display();
						}
					}
				break;
				
				//pod
				case 'p':
					pod = (Pod*) object;
					x = zombie->getX() - pod->getX();
					y = zombie->getY() - pod->getY();
					if((((x==-1)||(x==1))&&(y==0))||(((y==-1)||(y==1))&&(x==0)))
					{
						ss << "Zombie " << zombie->getSymbol() << " traveled to Pod at x = " << pod->getX()+1 << ", y = " << pod->getY()+1 << std::endl;
						if(this->control!=nullptr)
						{
							this->control->setStatusTxt(ss.str());
							//this->control->display();
						}
					}
				break;
				
				//trail
				case '.':
					trail = (Trail*) object;
					x = zombie->getX() - trail->getX();
					y = zombie->getY() - trail->getY();
					if((((x==-1)||(x==1))&&(y==0))||(((y==-1)||(y==1))&&(x==0)))
					{
						ss << "Zombie " << zombie->getSymbol() << " traveled to Trail at x = " << trail->getX()+1 << ", y = " << trail->getY()+1 << std::endl;
						if(this->control!=nullptr)
						{
							this->control->setStatusTxt(ss.str());
							//this->control->display();
						}
					}
				break;
			}
		}
	}
	
	
	
	std::ostream& Gameboard::output(std::ostream& _os)
	{
		//int rowCount;
		//int columnCount;
		//int zombieCount;
		int i = 0;
		int j = 0;
		_os << "[Gameboard]" << std::endl;
		_os << "rowCount=" << this->rowCount << std::endl;
		_os << "columnCount=" << this->columnCount << std::endl;
		_os << "zombieCount=" << this->zombieCount << std::endl;
		for(i = 0; i < this->rowCount; ++i)
		{
			for(j=0; j < this->columnCount; ++j)
			{
				Object* obj = &(this->getObjectAt(j,i));
				obj->output(_os);
			}
			
		}
		j = 0;
		j = this->getZombieCount();
		for(i=0; i < j ; ++i)
		{
			Zombie& zombie = this->getZombie(i);
			if((zombie.getX()<0)||(zombie.getY()<0))
			{
				zombie.output(_os);
			}
		}
		if(this->control!=nullptr)
		{
			if((this->control->getAlien().getX()<0)||(this->control->getAlien().getY()<0))
			{
				this->control->getAlien().output(_os);
			}
		}
		return _os;
	}
	
	
	std::istream& Gameboard::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int count = 0;
		int equalSign = 0;
		int _rowC = 0;
		int _colC = 0;
		int _zomC = 0;
		int i = 0;
		int j = 0;
		int k = 0;
		int x = 0;
		int y = 0;
		Zombie* zombie = nullptr;
		Arrow* arrow = nullptr;
		Health* health = nullptr;
		Rock* rock = nullptr;
		Space* space = nullptr;
		Trail* trail = nullptr;
		Pod* pod = nullptr;
		while(_in.getline(_data,dsize))
		{
			if((count=_in.gcount())>0)
			{
				data = _data;
				
				if(data.at(0)=='[')
				{
					
					if((_rowC>0)&&(_colC>0)&&(_zomC>0))
					{
						this->rowCount = _rowC;
						this->columnCount = _colC;
						this->zombieCount = _zomC;
						this->cleanUpZombie();
						this->cleanUpObject();
						this->fill();
						this->fillZombies();
						_rowC = -1;
						_colC = -1;
						_zomC = -1;
					
					}
					if(data=="[Alien]")
					{
						if(this->control!=nullptr)
						{
							this->control->getAlien().load(_in);
							x = this->control->getAlien().getX();
							y = this->control->getAlien().getY();
							if((x>=0)&&(y>=0))
								this->placeAlien(this->control->getAlien(), x, y);
						}
					}
					else
					{
						if(data=="[Zombie]")
						{
							zombie = new Zombie(*this);
							zombie->load(_in);
							x = zombie->getX();
							y = zombie->getY();
							i = 0;
							j = ((int)zombie->getSymbol());
							if(j>65)
							{
								j -= 65;
							}
							else
							{
								j -= 49;
							}
							k=0;
							for(std::list<Zombie*>::iterator it = this->zombies.begin();(i==0)&&(it!=this->zombies.end()); it++)
							{
								if(k==j)
								{
									*it = zombie;
									++i;
								}
								++k;
							}
							if(i==0)
								this->zombies.push_back(zombie);
							if((x>=0)&&(y>=0))
								this->setObjectAt(*zombie,x,y);
						}
						else
						{
							if(data=="[Arrow]")
							{
								arrow = new Arrow();
								arrow->load(_in);
								x = arrow->getX();
								y = arrow->getY();
								this->setObjectAt(*arrow,x,y);
								
							}
							else
							{
								if(data=="[Health]")
								{
									health = new Health();
									health->load(_in);
									x = health->getX();
									y = health->getY();
									this->setObjectAt(*health,x,y);
								}
								else
								{
									if(data=="[Rock]")
									{
										rock = new Rock();
										rock->load(_in);
										x = rock->getX();
										y = rock->getY();
										this->setObjectAt(*rock,x,y);
									}
									else
									{
										if(data=="[Space]")
										{
											space = new Space();
											space->load(_in);
											x = space->getX();
											y = space->getY();
											this->setObjectAt(*space,x,y);
										}
										else
										{
											if(data=="[Trail]")
											{
												trail = new Trail();
												trail->load(_in);
												x = trail->getX();
												y = trail->getY();
												this->setObjectAt(*trail,x,y);
											}
											else
											{
												if(data=="[Pod]")
												{
													pod = new Pod();
													pod->load(_in);
													x = pod->getX();
													y = pod->getY();
													this->setObjectAt(*pod,x,y);
												}
											}
										}
									}
									
								}
							}
							
						}
					}
					
				}
				else
				{
					equalSign = data.find('=');
					if((equalSign>=0)&&((equalSign+1)<count))
					{
						const std::string parameter = data.substr(0,equalSign);
						const std::string value = data.substr(equalSign+1);
						std::cout << "gameboard load  parameter=" << parameter << ",value="<< value << std::endl;
						if(parameter=="rowCount")
						{
							
							i = (int) std::stoul(value);
							_rowC = i;
							
						}
						else
						{
							if(parameter=="columnCount")
							{
								i = (int) std::stoul(value);
								_colC = i;
								
							}
							else
							{
								if(parameter=="zombieCount")
								{
									i = (int) std::stoul(value);
									_zomC = i;
								}
							}
							
						}
					}
				}
				
			}
		}
		return _in;
	}
	
	
	
	void Gameboard::cleanUpZombie()
	{
		Zombie* ptr = nullptr;
		char ch = 0;
		for(std::list<Zombie*>::iterator it = this->zombies.begin(); it!=(this->zombies.end()); )
		{
			ptr = *it;
			this->setObjectAt(*(new Space()), ptr->getX(), ptr->getY());
			it = this->zombies.erase(it);
			delete ptr;
					
		}
		
		
	}
	
	
	void Gameboard::cleanUpObject()
	{
		Object* ptr = nullptr;
		for(std::list<std::list<Object*> >::iterator it = this->objects.begin(); it != this->objects.end();)
		{
			for(std::list<Object*>::iterator inner_it = it->begin(); inner_it!= it->end();)
			{
				ptr = *inner_it;
				inner_it = it->erase(inner_it);
				if((this->control!=nullptr)&&(ptr!=(&(this->control->getAlien()))))
				{
					delete ptr;
				}
				
			}
			it = this->objects.erase(it);
		}
		
		
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
	
		
	void Object::setControl(Control* ptr)
	{
		this->control = ptr;
	}
	

	
	std::ostream& Object::output(std::ostream& _ostream) const
	{
		_ostream << "x="<< this->x << std::endl;
		_ostream << "y="<< this->y << std::endl;
		_ostream << "symbol="<< this->symbol << std::endl;
		return _ostream;
	}
	
	std::istream& Object::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int equalSign = 0;
		int count = 0;
		int i = 0;
		while((i<2)&&(_in.peek()!='[')&&(_in.getline(_data,dsize)))
		{
			count = _in.gcount() - 1;
			data = _data;
			if(count>0)
			{
				equalSign = data.find('=');
				if((equalSign+1)<count)
				{
					const std::string parameter = data.substr(0,equalSign);
					const std::string value = data.substr(equalSign+1);
					if(parameter=="x")
					{
						this->setX((int)std::stoul(value));
						++i;
					}
					else
					{
						if(parameter=="y")
						{
							this->setY((int)std::stoul(value));
							++i;
						}
						else
						{
							if(parameter=="symbol")
							{
								this->setSymbol(value.at(0));
								++i;
							}
						}
					}
					
				}
			}
		}
		return _in;
	}
	
	
	
	StoryCharacter::StoryCharacter(Gameboard& board): gameboard(board)
	{
		
	}
	
	
	
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
	
	

	void StoryCharacter::attack(StoryCharacter& storyCharacter)
	{
		
	}


	int StoryCharacter::attacked(const int damage)
	{
		int total = this->life;
		total -=  damage;
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

	
	
	
	
	
	Alien::Alien(Gameboard& _gb):StoryCharacter(_gb),movement(0)
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
	
	
	int Alien::getMovement() const
	{
		return this->movement;
	}
	
	void Alien::setMovement(int _movement)
	{
		this->movement = _movement;
	}
	
	int Alien::move()
	{
		int next = 0;
		switch(this->movement)
		{
			case 0:
				next = -1;
			break;
			
			//right
			case 1:
				next = this->getX() + 1;
			break;
			//bottom
			case 2:
				next = this->getY() + 1;
			break;
			//left
			case 3:
				next = this->getX() - 1;
			break;
			//up
			case 4:
				next = this->getY() - 1;
			break;
			
		}
		return next;
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
			// when x < 0; y < 0; meaning it is terminated
			enemy.setX(-1);
			enemy.setY(-1);
			ptr = new Space();
			this->gameboard.setObjectAt(*ptr, x, y);
			
		}
		else
		{
			this->setMovement(0);
			ss << "Zombie " << enemy.getSymbol() << " Survived with Life " << enemy.getLife() << "!!! Zombie "<< enemy.getSymbol() << " ->Alien: Prepared for Worst!!!" << std::endl;
			ss << "Alien Stopped at x = " << this->getX() << ", y = " << this->getY() << std::endl;
		}
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
			//this->control->display();
		}
	}
	
	void Alien::attack(Zombie& enemy, Pod& pod)
	{
		int x = 0;
		int y = 0;
		Object* ptr = nullptr;
		std::stringstream ss;
		int level = enemy.getLife() ;
		int damage = level - pod.getAttackPower();
		//std::cout << "alien attacks Zombie enemy" << std::endl;
		ss << "(Zombie " << enemy.getSymbol() << " Life) "<< level << " - (Alien Attack Power!) " << this->getAttackPower() << " = ";
		ss	<< " (Zombie " << enemy.getSymbol() << " After Attacked)" << damage << std::endl;
		enemy.setLife(damage);
		
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
			ss << "Zombie " << enemy.getSymbol() << " Survived with Life " << enemy.getLife() << "!!! Zombie "<< enemy.getSymbol() << " ->Alien: Prepared for Worst!!!" << std::endl;
		}
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
			//this->control->display();
		}
	}
	
	Object& Alien::yields()
	{
		Trail* ptr = new Trail();
		ptr->setControl(this->control);
		ptr->setGameboard(&(this->gameboard));
		return *ptr;
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
	{	//perhaps dangerous to delete argument address
		std::stringstream ss;
		
		ss << "Alien discovered Object Under Rock" << std::endl;
		Object& obj = rock.reveal();
		this->gameboard.setObjectAt(obj,rock.getX(), rock.getY());
		if((&obj)!=&rock)
		{
			delete &rock;
		}
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
			//this->control->display();
		}
		
	}
	
	void Alien::collect(Pod& pod)
	{	//perhaps dangerous to delete argument address
		std::stringstream ss;
		int x =0;
		int y = 0;
		int x1 = 0;
		int y1 = 0;
		int dx = 0;
		int dy = 0;
		int range = 0;
		int count = 0;
		int i = 0;
		int unlucky = 0;
		int attackCount = 0;
		std::list<Zombie*> targetCandidates;
		ss << "Alien utilizing Pod" << std::endl;
		Zombie* pz = nullptr;
		
		
		x1 = pod.getX();
		y1 = pod.getY();
		range = pod.getAttackRange();
		
		count = this->gameboard.getZombieCount();
		for(i=0; i < count ; ++i)
		{
			pz = &(this->gameboard.getZombie(i));
			if(pz!=nullptr)
			{
				x = pz->getX();
				y = pz->getY();
				if((x>=0)&&(y>=0))
				{	//living zombie would not have negative location
					dx = x - x1;
					dy = y - y1;
					if(dx<0)
						dx = -dx;
					if(dy<0)
						dy = -dy;
					if((dx<=range)&&(dy<=range))
					{
						targetCandidates.push_back(pz);
					}
				}
			}
		}
		count = targetCandidates.size();
		if(count>0)
			unlucky = std::rand()%count;
		pz = nullptr;
		i = 0;
		for(std::list<Zombie*>::iterator it = targetCandidates.begin(); (attackCount==0)&&(it!=targetCandidates.end()); it++)
		{
			if(i==unlucky)
			{
				pz = *it;
				x = pz->getX();
				y = pz->getY();
				if((x>=0)&&(y>=0))
				{	//living zombie would not have negative location
					dx = x - x1;
					dy = y - y1;
					if(dx<0)
						dx = -dx;
					if(dy<0)
						dy = -dy;
					if((dx<=range)||(dy<=range))
					{
						ss << "Unlucky Zombie " << pz->getSymbol() << ", x = " << x+1 << ", y = " << y+1 << " within Pod Attack Range " << range << std::endl;
						ss << "With Pod at x ="<< x1+1 << ", y = " <<  y1+1 << ", Alien attacks Zombie " << pz->getSymbol() << ", x = " << x+1 << ", y = " << y+1  << std::endl;
						this->attack(*pz, pod);
						++attackCount;
					}
				}
			}
			++i;
		}
		ss << "Alien continues traveling.. at location x =" << this->getX()+1 << ", y = " << this->getY()+1 << std::endl;
		
		if(this->control!=nullptr)
		{
			this->control->addStatusTxt(ss.str());
			//this->control->display();
		}
		
	}
	
	std::ostream& Alien::output(std::ostream& _os) const
	{
		_os << "[Alien]" << std::endl;
		_os << "x=" << this->x << std::endl;
		_os << "y=" << this->y << std::endl;
		_os << "symbol=" << this->symbol << std::endl;
		_os << "life=" << this->life << std::endl;
		_os << "attackPower=" << this->attackPower << std::endl;
		_os << "movement=" << this->movement << std::endl;
		_os << "maxLife=" << this->maxLife << std::endl;
		_os << "maxAttackPower=" << this->maxAttackPower << std::endl;
		return _os;
	}
	
	std::istream& Alien::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int equalSign = 0;
		int count = 0;
		int i = 0;
		while((i<8)&&(_in.peek()!='[')&&(_in.getline(_data,dsize)))
		{
			count = _in.gcount() - 1;
			data = _data;
			if(count>0)
			{
				equalSign = data.find('=');
				if((equalSign+1)<count)
				{
					const std::string parameter = data.substr(0,equalSign);
					const std::string value = data.substr(equalSign+1);
					if(parameter=="x")
					{
						this->setX(std::stoi(value));
						++i;
					}
					else
					{
						if(parameter=="y")
						{
							this->setY(std::stoi(value));
							++i;
						}
						else
						{
							if(parameter=="symbol")
							{
								this->setSymbol(value.at(0));
								++i;
							}
							else
							{
								if(parameter=="life")
								{
									this->setLife(std::stoi(value));
									++i;
								}
								else
								{
									if(parameter=="attackPower")
									{
										this->setAttackPower((int)std::stoul(value));
										++i;
									}
									else
									{
										if(parameter=="movement")
										{
											this->setMovement((int)std::stoul(value));
											++i;
										}
										else
										{
											if(parameter=="maxLife")
											{
												this->setMaxLife((int)std::stoul(value));
												++i;
											}
											else
											{
												if(parameter=="maxAttackPower")
												{
													this->setMaxAttackPower((int)std::stoul(value));
													++i;
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
		}
		return _in;
		
	}
	
	
	
	Zombie::Zombie(Gameboard& gb):StoryCharacter(gb),attackRange(0),movement(0)
	{
		this->symbol= '1';
		this->setMaxAttackPower(100);
		//this->setMaxLife(500);
		this->setMaxLife(3);
		
	}
	
	Zombie::Zombie(Gameboard& gb, const char ch):StoryCharacter(gb), attackRange(1),movement(0)
	{
		this->symbol = ch;
		this->setMaxAttackPower(100);
		//this->setMaxLife(500);
		this->setMaxLife(3);
	}
	
	
	Zombie::Zombie(Gameboard& gb, const char ch, const int _life, const int attack_power, const int attack_range)
		:StoryCharacter(gb),  attackRange(attack_range),movement(0)
	{
		this->symbol = ch;
		this->life = _life;
		this->attackPower = attack_power;
	}
	
	void Zombie::attack(Alien* alien)
	{
		std::stringstream ss;
		int x = 0;
		int y = 0;
		int x1 = 0;
		int y1 = 0;
		Space* space = nullptr;
		if(alien!=nullptr)
		{
			x = this->getX() + 1;
			y = this->getY() + 1;
			x1 = alien->getX() + 1;
			y1 = alien->getY() + 1;
			ss << "Alien x = "<< x1 << " y = " << y1;
			ss << " attacked by Zombie " << this->getSymbol()  << " x = " << x << " y = " << y ;
			ss << " range = "<< this->getAttackRange() << std::endl;
			ss << "(Alien life)" << alien->getLife() << " - (Zombie " << this->getSymbol() << " attack power)" << this->getAttackPower() << " = " ;
			alien->attacked(this->getAttackPower());
			ss << alien->getLife()  << std::endl;
			if(alien->getLife()<=0)
			{
				alien->setX(-1);
				alien->setY(-1);
				ss << "Alien doomed at x = " <<  x1 << ", y1 =" << y1 << " in attack launched by Zombie " << this->getSymbol() << std::endl;
				space = new Space();
				space->setX(x1-1);
				space->setY(y1-1);
				this->gameboard.setObjectAt(*space,x1-1,y1-1);
			
			}
			this->control->addStatusTxt(ss.str());
		}
		
	}
	
	Zombie::~Zombie()
	{
		//std::cout << "~Zombie " << this->getSymbol() << std::endl;
	}
	
	
	
	int Zombie::getAttackRange() const
	{
		return this->attackRange;
	}
	
	void Zombie::setAttackRange(const int _attackRange)
	{
		this->attackRange = _attackRange;
	}
	
	int Zombie::getMovement() const
	{
		return this->movement;
	}
	
	void Zombie::setMovement(int _movement)
	{
		this->movement = _movement;
	}
	
	int Zombie::move()
	{
		int next = 0;
		switch(this->movement)
		{
			case 0:
				next = -1;
			break;
			
			//right
			case 1:
				next = this->getX() + 1;
			break;
			//bottom
			case 2:
				next = this->getY() + 1;
			break;
			//left
			case 3:
				next = this->getX() - 1;
			break;
			//up
			case 4:
				next = this->getY() - 1;
			break;
			
		}
		return next;
	}
	
	std::ostream& Zombie::output(std::ostream& _os) const
	{
		_os << "[Zombie]" << std::endl;
		_os << "x=" << this->x << std::endl;
		_os << "y=" << this->y << std::endl;
		_os << "symbol=" << this->symbol << std::endl;
		_os << "life=" << this->life << std::endl;
		_os << "attackPower=" << this->attackPower << std::endl;
		_os << "attackRange=" << this->attackRange << std::endl;
		_os << "movement=" << this->movement << std::endl;
		_os << "maxLife=" << this->maxLife << std::endl;
		_os << "maxAttackPower=" << this->maxAttackPower << std::endl;
		
		return _os;
	}
	
	std::istream& Zombie::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int equalSign = 0;
		int count = 0;
		int i = 0;
		while((i<8)&&(_in.peek()!='[')&&(_in.getline(_data,dsize)))
		{
			count = _in.gcount() - 1;
			data = _data;
			if(count>0)
			{
				equalSign = data.find('=');
				if((equalSign+1)<count)
				{
					const std::string parameter = data.substr(0,equalSign);
					const std::string value = data.substr(equalSign+1);
					if(parameter=="x")
					{
						this->setX(std::stoi(value));
						++i;
					}
					else
					{
						if(parameter=="y")
						{
							this->setY(std::stoul(value));
							++i;
						}
						else
						{
							if(parameter=="symbol")
							{
								this->setSymbol(value.at(0));
								++i;
							}
							else
							{
								if(parameter=="life")
								{
									this->setLife(std::stoi(value));
									++i;
								}
								else
								{
									if(parameter=="attackPower")
									{
										this->setAttackPower((int)std::stoul(value));
										++i;
									}
									else
									{
										if(parameter=="attackRange")
										{
											this->setAttackRange(std::stoi(value));
											++i;
										}
										else
										{
											if(parameter=="movement")
											{
												this->setMovement((int)std::stoul(value));
												++i;
											}
											else
											{
												if(parameter=="maxLife")
												{
													this->setMaxLife((int)std::stoul(value));
													++i;
												}
												else
												{
													if(parameter=="maxAttackPower")
													{
														this->setMaxAttackPower((int)std::stoul(value));
														++i;
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
			}
		}
		return _in;
		
	}
	
	Object& Zombie::yields()
	{
		Object* ptr = new Space();
		ptr->setControl(this->control);
		return *ptr;
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
	
	
	
		
	std::ostream& Health::output(std::ostream& _os) const
	{
		_os << "[Health]" << std::endl;
		_os << "x=" << this->x << std::endl;
		_os << "y=" << this->y << std::endl;
		_os << "symbol=" << this->symbol << std::endl;	
		_os << "healingPoint=" << this->healingPoint << std::endl;
		
		
		return _os;
	}
	
	std::istream& Health::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int equalSign = 0;
		int count = 0;
		int i = 0;
		while((i<3)&&(_in.peek()!='[')&&(_in.getline(_data,dsize)))
		{
			count = _in.gcount() - 1;
			data = _data;
			if(count>0)
			{
				equalSign = data.find('=');
				if((equalSign+1)<count)
				{
					const std::string parameter = data.substr(0,equalSign);
					const std::string value = data.substr(equalSign+1);
					if(parameter=="x")
					{
						this->setX((int)std::stoul(value));
						++i;
					}
					else
					{
						if(parameter=="y")
						{
							this->setY((int)std::stoul(value));
							++i;
						}
						else
						{
							if(parameter=="symbol")
							{
								this->setSymbol(value.at(0));
								++i;
							}
							else
							{
								if(parameter=="healingPoint")
								{
									this->healingPoint = (int)std::stoul(value);
									++i;
								}
							}
						}
					}
					
				}
			}
		}
		return _in;
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
	
	
	
	
	int Arrow::getAttackPower() const
	{
		return this->attackPower;
	}
	
	
	
	
	std::ostream& Arrow::output(std::ostream& _os) const
	{
		_os << "[Arrow]" << std::endl;
		_os << "x=" << this->x << std::endl;
		_os << "y=" << this->y << std::endl;
		_os << "symbol=" << this->symbol << std::endl;	
		_os << "attackPower=" << this->attackPower << std::endl;
		return _os;
	}
	
	std::istream& Arrow::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int equalSign = 0;
		int count = 0;
		int i = 0;
		
		
		while((i<3)&&(_in.peek()!='[')&&(_in.getline(_data,dsize)))
		{
			data = _data;
			count = _in.gcount()-1;
			if(count>0)
			{
				equalSign = data.find('=');
				//std::cout << "arrow load equalSign " << equalSign << ",count=" << count << std::endl;
				if((equalSign+1)<count)
				{
					const std::string parameter = data.substr(0,equalSign);
					const std::string value = data.substr(equalSign+1);
					//std::cout << "arrow load parameter =" << parameter << ",value=" << value << std::endl; 
					if(parameter=="x")
					{
						this->setX((int)std::stoul(value));
						++i;
					}
					else
					{
						if(parameter=="y")
						{
							this->setY((int)std::stoul(value));
							++i;
						}
						else
						{
							if(parameter=="symbol")
							{
								this->setSymbol(value.at(0));
								++i;
							}
							else
							{
								if(parameter=="attackPower")
								{
									this->attackPower = (int)std::stoul(value);
									++i;
								}
								
							}
						}
					}
					
				}
			}
		}
		
		return _in;
	}
	
	
	
	std::ostream& Rock::output(std::ostream& _os) const
	{
		_os << "[Rock]" << std::endl;
		_os << "x=" << this->x << std::endl;
		_os << "y=" << this->y << std::endl;
		_os << "symbol=" << this->symbol << std::endl;	
		_os << "flipped=" ;
		if(this->flipped)
			_os << "1";
		else
			_os << "0";
		_os << std::endl;
		
		
		return _os;
	}
	
	std::istream& Rock::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int equalSign = 0;
		int count = 0;
		int i = 0;
		while((i<3)&&(_in.peek()!='[')&&(_in.getline(_data,dsize)))
		{
			count = _in.gcount() - 1;
			data = _data;
			if(count>0)
			{
				equalSign = data.find('=');
				if((equalSign+1)<count)
				{
					const std::string parameter = data.substr(0,equalSign);
					const std::string value = data.substr(equalSign+1);
					if(parameter=="x")
					{
						this->setX((int)std::stoul(value));
						++i;
					}
					else
					{
						if(parameter=="y")
						{
							this->setY((int)std::stoul(value));
							++i;
						}
						else
						{
							if(parameter=="symbol")
							{
								this->setSymbol(value.at(0));
								++i;
							}
							else
							{
								if(parameter=="filpped")
								{
									int check = (int)std::stoul(value);
									if(check==1)
									{
										this->flipped = true;
									}
									else
									{
										this->flipped = false;
										
									}
									++i;
								}
								
							}
						}
					}
					
				}
			}
		}
		return _in;
	}
	
	Rock::Rock(): flipped(false)
	{
		this->symbol = 'r';
		
		
	}
	
	//Rock::~Rock()
	//{
	//	
	//}
	
	
	
	void Rock::flip()
	{
		this->flipped = true;
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
	
	
	
	std::ostream& Space::output(std::ostream& _os) const
	{
		_os << "[Space]" << std::endl;
		_os << "x=" << this->x << std::endl;
		_os << "y=" << this->y << std::endl;
		_os << "symbol=" << this->symbol << std::endl;	
		return _os;
	}
	
	std::istream& Space::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int equalSign = 0;
		int count = 0;
		int i = 0;
		while((i<2)&&(_in.peek()!='[')&&(_in.getline(_data,dsize)))
		{
			count = _in.gcount() - 1;
			data = _data;
			if(count>0)
			{
				equalSign = data.find('=');
				if((equalSign+1)<count)
				{
					const std::string parameter = data.substr(0,equalSign);
					const std::string value = data.substr(equalSign+1);
					if(parameter=="x")
					{
						this->setX((int)std::stoul(value));
						++i;
					}
					else
					{
						if(parameter=="y")
						{
							this->setY((int)std::stoul(value));
							++i;
						}
						else
						{
							if(parameter=="symbol")
							{
								this->setSymbol(value.at(0));
								++i;
							}
						}
					}
					
				}
			}
		}
		return _in;
	}
	
	Pod::Pod() : attackPower(10),attackRange(1)
	{
		this->symbol = 'p';
		
	}
	
	//Pod::~Pod()
	//{
	//	
	//}
	
	int Pod::getAttackPower() const
	{
		return this->attackPower;
	}
	
	void Pod::setAttackPower(int value) 
	{
		this->attackPower = value;
	}
	
	int Pod::getAttackRange() const
	{
		return this->attackRange;
	}
	
	void Pod::setAttackRange(int value) 
	{
		this->attackRange = value;
	}
	
	
	
	std::ostream& Pod::output(std::ostream& _os) const
	{
		_os << "[Pod]" << std::endl;
		_os << "x=" << this->x << std::endl;
		_os << "y=" << this->y << std::endl;
		_os << "symbol=" << this->symbol << std::endl;	
		_os << "attackPower= " << this->attackPower << std::endl;
		_os << "attackRange= " << this->attackRange << std::endl;
		
		
		return _os;
	}
	
	std::istream& Pod::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int equalSign = 0;
		int count = 0;
		int i = 0;
		while((i<4)&(_in.peek()!='[')&&(_in.getline(_data,dsize)))
		{
			count = _in.gcount() - 1;
			data = _data;
			if(count>0)
			{
				equalSign = data.find('=');
				if((equalSign+1)<count)
				{
					const std::string parameter = data.substr(0,equalSign);
					const std::string value = data.substr(equalSign+1);
					if(parameter=="x")
					{
						this->setX((int)std::stoul(value));
						++i;
					}
					else
					{
						if(parameter=="y")
						{
							this->setY((int)std::stoul(value));
							++i;
						}
						else
						{
							if(parameter=="symbol")
							{
								this->setSymbol(value.at(0));
								++i;
							}
							else
							{
								if(parameter=="attackPower")
								{
									this->setAttackPower((int)std::stoul(value));
									++i;
								}
								else
								{
									if(parameter=="attackRange")
									{
										this->setAttackRange((int)std::stoul(value));
										++i;
									}
								}
							}
						}
					}
					
				}
			}
		}
		return _in;
	}
	
	Trail::Trail():gameboard(nullptr)
	{
		this->symbol = '.';
		
	}
	
	void Trail::setGameboard(Gameboard* _gb)
	{
		this->gameboard = _gb;
	}
	
	Object& Trail::reveal()
	{
		Object* ptr = nullptr;
		Pod* podPtr = nullptr;
		int randomNumber = std::rand()%8;
		char ch = 0;
		const int attackPower = 10;
		const int healingPoint = 20;
		int smaller = 0;
		int randomRange = 0;
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
				podPtr = (Pod*) ptr;
				if(podPtr!=nullptr)
				{
					if(this->gameboard!=nullptr)
					{	
						smaller = this->gameboard->getRowCount();
						if(this->gameboard->getColumnCount()<smaller)
							smaller = this->gameboard->getColumnCount();
						do
						{
							randomRange  = std::rand()%smaller;
						
						}while(randomRange==0);
						podPtr->setAttackRange(randomRange);
						podPtr = nullptr;
					}
				}
				
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
		
		ss << "Trail at x = " << this->getX()+1 << ", y = " << this->getY()+1 << " => (" << ch << ")" <<std::endl;
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
	
	
	
	std::ostream& Trail::output(std::ostream& _os) const
	{
		_os << "[Trail]" << std::endl;
		_os << "x=" << this->x << std::endl;
		_os << "y=" << this->y << std::endl;
		_os << "symbol=" << this->symbol << std::endl;			
		return _os;
	}
	
	std::istream& Trail::load(std::istream& _in)
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int equalSign = 0;
		int count = 0;
		int i = 0;
		while((i<2)&&(_in.peek()!='[')&&(_in.getline(_data,dsize)))
		{
			count = _in.gcount() - 1;
			data = _data;
			if(count>0)
			{
				equalSign = data.find('=');
				if((equalSign+1)<count)
				{
					const std::string parameter = data.substr(0,equalSign);
					const std::string value = data.substr(equalSign+1);
					if(parameter=="x")
					{
						this->setX((int)std::stoul(value));
						++i;
					}
					else
					{
						if(parameter=="y")
						{
							this->setY((int)std::stoul(value));
							++i;
						}
						else
						{
							if(parameter=="symbol")
							{
								this->setSymbol(value.at(0));
								++i;
							}
						}
					}
					
				}
			}
		}
		return _in;
	}
	
	Control::Control(Gameboard& gb, Alien& al):gameboard(gb), alien(al),commandTxt(),statusTxt(),statusCode(0),turnCount(0), currentZombieIndex(-1),retainOnce(false)
	{
		this->gameboard.setControl(this);
		this->alien.setControl(this);
	}
	
	
	Control::~Control()
	{
		
	}
	
	Alien& Control::getAlien()
	{
		return this->alien;
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
		int x = 0;
		int y = 0;
		int displayColumnCount = 0;
		const int maxColumnCount = 80;
		
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
			//std::cout << std::endl << ((this->turnCount==(j+1))?'*':' ');
			std::cout << std::endl << ((this->currentZombieIndex==j)? '*' : ' ');
			
			std::cout << "Zombie " << zombie.getSymbol() << "  :    Life " << zombie.getLife() << ", Attack " << zombie.getAttackPower() ;
			std::cout << ", Range " << zombie.getAttackRange() ;
			for(i=0; i < 4; ++i)
			{
				std::cout << ' ';
			}
			x = zombie.getX();
			y = zombie.getY();
			if((x<0)||(y<0))
			{
				std::cout << "***Terminated***";	
				for(i=0; i < 3 ; ++i)
				{
					std::cout << ' ';
				}
				std::cout << "x " << x << ", y " << y << std::endl;
			}
			else
			{
				for(i=0; i < 8 ; ++i)
				{
					std::cout << ' ';
				}
				std::cout << "x " << x+1 << ", y " << y+1 << std::endl;
			}
			
		}
		
	}
	
	void Control::requestInput()
	{
		std::cout << std::endl << "command:";
		std::cin >> this->commandTxt;
		std::cout << std::endl;
	}
	
	
	void Control::processInput()
	{
		
		std::transform(this->commandTxt.begin(), this->commandTxt.end(),this->commandTxt.begin(),tolower);
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
				this->addStatusTxt("Quit Game");
				
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
										this->disableFlipTurnForOnce();
									}
									else
									{
										if(this->commandTxt=="load")
										{
											this->processCommandLoad();
											this->disableFlipTurnForOnce();
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
		
		this->gameboard.alienMove(4);
		this->gameboard.refreshAllTrail();
	}
	
	
	
	
	
	void Control::processCommandDown()
	{
			
		this->gameboard.alienMove(2);
		this->gameboard.refreshAllTrail();
	}
	
	
	void Control::processCommandLeft()
	{
		
		this->gameboard.alienMove(3);
		this->gameboard.refreshAllTrail();
	}
	
	void Control::processCommandRight()
	{
				
		this->gameboard.alienMove(1);
		this->gameboard.refreshAllTrail();
	}
	
	void Control::processCommandArrow()
	{
		int x = -1;
		int y = -1;
		int x1 = -1;
		int y1= -1;
		std::cout << "x axis of arrow to change:";
		std::cin >> x;
		std::cout << std::endl << "y axis of arrow to change:";
		std::cin >> y;
		bool result = false;
		Object* obj = nullptr;
		char oldCh = 0;
		char ch = 0;
		x1 = x -1;
		y1 = y -1;
		std::stringstream ss;
		
		if((x1>=0)&&(y1>=0))
		{
			if(this->gameboard.isArrow(x1,y1))
			{
				obj = &(this->gameboard.getObjectAt(x1,y1));
				if(obj!=nullptr)
				{
					oldCh = obj->getSymbol();
					std::cout << std::endl << "Arrow at x =" << x << ", y= "<< y << " " << oldCh << " to be altered to (<, >, ^, v) ";
					std::cin >> ch;
					if((ch=='<')||(ch!='^')||(ch!='>')||(ch!='v'))
					{
						obj->setSymbol(ch);
						result = true;
					}
				}
			}
		}
		if(result)
		{
			ss << std::endl << "Arrow at x =" << x << ", y= "<< y << " " << oldCh << " becomes  " << ch << std::endl;
		}
		else
		{
			ss << std::endl << "Unable to conduct command arrow" << std::endl;
		}
		this->addStatusTxt(ss.str());
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
		std::stringstream ss;
		std::ofstream outputFile("GameFile.save", std::ofstream::trunc);
		if(outputFile.is_open())
		{
			outputFile << "[Control]" << std::endl;
			outputFile << "commandTxt=" << this->commandTxt << std::endl;
			outputFile << "statusTxt=" << this->statusTxt << std::endl;
			outputFile << "turnCount=" << this->turnCount << std::endl;
			this->gameboard.output(outputFile);
			outputFile.close();
			ss << "Game Saved" << std::endl;
			this->addStatusTxt(ss.str());
		}
		else
		{
			ss << "GError to Save Game" << std::endl;
			this->addStatusTxt(ss.str());
		}
		
	}
	
	void Control::processCommandLoad()
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int count = 0;
		int equalSign = -1;
		std::string mainItem;
		std::stringstream ss;
		std::ifstream inputFile("GameFile.save", std::istream::in);
		if(inputFile.is_open())
		{
			while(inputFile.getline(_data,dsize))
			{
				if((count=inputFile.gcount())>0)
				{	
					data = _data;
					std::cout << "load data=" << data << std::endl;
					if(data.at(0)=='[')
					{
						mainItem = data;
					}
					if(mainItem=="[Control]")
					{
						equalSign = -1;
						equalSign = data.find("=");
						if((equalSign>=0)&&((equalSign+1)<count))
						{
							const std::string& parameter = data.substr(0,equalSign);
							const std::string& value = data.substr(equalSign+1);
							if(parameter=="commandTxt")
							{
								this->commandTxt = value;
							}
							else
							{
								if(parameter=="statusTxt")
								{
									this->statusTxt = value;
								}
								else
								{
									if(parameter=="turnCount")
									{
										this->turnCount = (int)std::stoul(value);
									}
								}
							}
							
						}
					}
					else
					{
						if(mainItem=="[Gameboard]")
						{
							this->gameboard.load(inputFile);
						}
						
					}
					
					
				}
			}
			inputFile.close();
			ss << "Game Loaded Successfully" << std::endl;
			this->setStatusTxt(ss.str());
		}
		else
		{
			ss << "Unable to load Game" << std::endl;
			this->setStatusTxt(ss.str());
		}
	}
	
	
	
	int Control::work()
	{
		int index = 0;
		int direction = 0;
		std::stringstream ss;
		int gameResult = 0;
		
		while(this->statusCode==0)
		{	
			index = 0;
			if(this->turnCount==0)
			{
				this->currentZombieIndex = -1;
				this->display();
				this->requestInput();
				this->processInput();
				if(this->commandTxt!="quit")
				{
					this->display();
					pf::Pause();
				}
			}
			else
			{
				index = this->pickZombie(this->turnCount);
				if(index>=0)
				{
					
					Zombie& zombie = this->gameboard.getZombie(index);
					this->currentZombieIndex = index;
					ss << "Zombie " << zombie.getSymbol() << ": IT IS MY TURN NOW!!" << std::endl;  
					direction = this->pickDirection(zombie);
					ss << "Zombie " << zombie.getSymbol() << ": To ";
					switch(direction)
					{
						case 0:
							ss << " LEFT <- " << std::endl;
						break;
						
						case 1:
								ss << " UP ^ " << std::endl;
						break;
						
						case 2:
							ss << " DOWN V " << std::endl;
						break;
						
						case 3:
							ss << " RIGHT -> " << std::endl;
						break;
					}
					this->addStatusTxt(ss.str());
					this->display();
					ss.str("");
					pf::Pause();
					this->zombieWalk(zombie,direction);
					this->display();
					pf::Pause();
					
					
				}
				
				
			}
			gameResult = this->isGameOver();
			if(gameResult==0)
			{
				//game is still ongoing
				this->flipTurn();
			}
			else
			{
				this->statusCode = gameResult;
				if(gameResult==-1)
				{
					ss << "You Beeen Defeated" << std::endl;
				}
				else
				{
					ss << "You Are Victory" << std::endl;
				}
				this->addStatusTxt(ss.str());
				ss.str("");
			}
		}
		this->display();
		
		return this->statusCode;
	}
	

	
	int Control::pickZombie(const int turn)
	{
		int i = 0;
		int zombieIndex = turn - 1;
		int zombieCount = 0;
				
		zombieCount = this->gameboard.getZombieCount();
		
		if(zombieCount>zombieIndex)
		{
			
			Zombie& zombie = this->gameboard.getZombie(zombieIndex);
			if((zombie.getX()<0)||(zombie.getY()<0))
			{
				zombieIndex = -1;
			}

		}
		else
		{
			zombieIndex = -1;
		}
		return zombieIndex;
		
	}
	
	int Control::pickDirection(Zombie& zombie) const
	{
		bool next = true;
		bool proceed = true;
		bool proceed1 = true;
		int borderY = 0;
		int borderX = 0;
		int i = 0;
		int x = 0;
		int y = 0;
		int ax =0;
		int ay = 0;
		int randomDirection = 0;
		int zombieCount = 0;
		int nextX = -1;
		int nextY = -1;
		int x1 = 0;
		int y1 = 0;
		x = zombie.getX();
		y = zombie.getY();
		ax = this->alien.getX();
		ay = this->alien.getY();
		zombieCount = this->gameboard.getZombieCount();
		borderX = this->gameboard.getColumnCount();
		borderY = this->gameboard.getRowCount();
		while(next)
		{
			proceed = true;
			proceed1 = true;
			
			randomDirection = std::rand()%4;
			switch(randomDirection)
			{
				//left
				case 0:
					nextX = x -1;
					proceed = (nextX>=0)&&((nextX-ax)!=0)&&((y-ay)!=0);
				break;
				
				//up
				case 1:
					nextY = y -1;
					proceed = (nextY>=0)&&((nextY-ay)!=0)&&((x-ax)!=0);
				break;
				
				//down
				case 2:
					nextY = y + 1;
					proceed = (nextY<borderY)&&((nextY-ay)!=0)&&((x-ax)!=0);
				break;
				
				//right
				case 3:
					nextX = x + 1;
					proceed = (nextX<borderX)&&((nextX-ax)!=0)&&((y-ay)!=0);
				break;
				
				
			}
			
			
			
			for(i=0; (proceed)&&(proceed1)&&(i < zombieCount); ++i)
			{
				Zombie& other = this->gameboard.getZombie(i);
				
				if((&other)!=(&zombie))
				{
					x1 = other.getX();
					y1 = other.getY();
					if((x1>=0)&&(y1>=0))
					{
						switch(randomDirection)
						{
							//left
							case 0:
								proceed1 = ((y !=y1)||((x-1-x1)!=0));
							break;
							
							//up
							case 1:
								proceed1 = ((x != x1)||((y-1-y1)!=0));
							break;
							
							//down
							case 2:
								proceed1 = ((x != x1)||((y+1-y1)!=0));
							break;
							
							//right
							case 3:
								proceed1 = ((y != y1)||((x+1-x1)!=0));
							break;
							
							
						}
					}
				}
			}
			next = ((proceed==false)||(proceed1==false));
		}
		return randomDirection;
	}
	
	void Control::zombieWalk(Zombie& zombie, const int direction)
	{
		//int x  = zombie.getX();
		//int y = zombie.getY();
		switch(direction)
		{
			//left
			case 0:
				//zombie.setNextTranslationX(-1);
				//zombie.setNextTranslationY(0);
				//zombie.readyToGo();
				//zombie._move(x-1,y);
				
				//this->gameboard.refreshAllTrail();
				
				this->gameboard.zombieMove(&zombie, 3);
				
			break;
			
			//up
			case 1:
				//zombie.setNextTranslationX(0);
				//zombie.setNextTranslationY(-1);
				//zombie.readyToGo();
				//zombie._move(x,y-1);
				
				this->gameboard.zombieMove(&zombie, 4);
			break;
			
			//down
			case 2:
				//zombie.setNextTranslationX(0);
				//zombie.setNextTranslationY(1);
				//zombie.readyToGo();
				//zombie._move(x,y+1);
				
				this->gameboard.zombieMove(&zombie, 2);
			break;
			
			//right
			case 3:
				//zombie.setNextTranslationX(1);
				//zombie.setNextTranslationY(0);
				//zombie.readyToGo();
				//zombie._move(x+1,y);
				
				this->gameboard.zombieMove(&zombie, 1);
			break;
		}
	}
	 
	void Control::flipTurn()
	{
		if(retainOnce)
		{
			this->retainOnce = false;
		}
		else
		{
			++(this->turnCount);
			this->turnCount = this->turnCount%(this->gameboard.getZombieCount()+1);
		}
	}
	
	void Control::disableFlipTurnForOnce()
	{
		this->retainOnce = true;
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
	
	int Control::isGameOver()
	{
		int result = 0;
		int life = 0;
		int x = 0;
		int y = 0;
		int count = 0;
		int flag = 1;
		int i = 0;
		if((this->alien.getLife()<=0)||(this->alien.getX()<0)||(this->alien.getY()<0))
		{
			result = -1;
		}
		else
		{
			count = this->gameboard.getZombieCount();
			for(i=0; (i < count)&&(flag==1); ++i)
			{
				Zombie& zombie = this->gameboard.getZombie(i);
				life = zombie.getLife();
				x = zombie.getX();
				y = zombie.getY();
				if((life>0)||(x>=0)||(y>=0))
				{
					flag = 0;
				}
			}
			if(flag==0)
				result = 0;
			else
				result = 1;
		}
		//result = 1 if zombie loss; result = 0 if game not over yet; result = -1 alien loss
		return result;
		
	}
			
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
		std::stringstream ss;
		std::ofstream outputFile("GameFile.save", std::ofstream::trunc);
		if(outputFile.is_open())
		{
			outputFile << "[Control]" << std::endl;
			outputFile << "commandTxt=" << this->commandTxt << std::endl;
			outputFile << "statusTxt=" << this->statusTxt << std::endl;
			outputFile << "turnCount=" << this->turnCount << std::endl;
			this->gameboard.output(outputFile);
			outputFile.close();
			ss << "Game Saved" << std::endl;
			this->addStatusTxt(ss.str());
		}
		else
		{
			ss << "GError to Save Game" << std::endl;
			this->addStatusTxt(ss.str());
		}
		
	}
	
	void Control::processCommandLoad()
	{
		const int dsize = 1024;
		char _data[dsize];
		std::string data;
		int count = 0;
		int equalSign = -1;
		std::string mainItem;
		std::stringstream ss;
		std::ifstream inputFile("GameFile.save", std::istream::in);
		if(inputFile.is_open())
		{
			while(inputFile.getline(_data,dsize))
			{
				if((count=inputFile.gcount())>0)
				{	
					data = _data;
					std::cout << "load data=" << data << std::endl;
					if(data.at(0)=='[')
					{
						mainItem = data;
					}
					if(mainItem=="[Control]")
					{
						equalSign = -1;
						equalSign = data.find("=");
						if((equalSign>=0)&&((equalSign+1)<count))
						{
							const std::string& parameter = data.substr(0,equalSign);
							const std::string& value = data.substr(equalSign+1);
							if(parameter=="commandTxt")
							{
								this->commandTxt = value;
							}
							else
							{
								if(parameter=="statusTxt")
								{
									this->statusTxt = value;
								}
								else
								{
									if(parameter=="turnCount")
									{
										this->turnCount = (int)std::stoul(value);
									}
								}
							}
							
						}
					}
					else
					{
						if(mainItem=="[Gameboard]")
						{
							this->gameboard.load(inputFile);
						}
						
					}
					
					
				}
			}
			inputFile.close();
			ss << "Game Loaded Successfully" << std::endl;
			this->setStatusTxt(ss.str());
		}
		else
		{
			ss << "Unable to load Game" << std::endl;
			this->setStatusTxt(ss.str());
		}
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
