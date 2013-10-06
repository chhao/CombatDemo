//
//  HelperUtil.cpp
//  FairyTales
//
//  Created by Hao Chen on 3/31/13.
//
//

#include "HelperUtil.h"
#include <iomanip>
#include "json_lib.h"
#include <fstream>

using namespace cocos2d;

bool isHit(cocos2d::CCSprite* sprite, cocos2d::CCTouch *pTouch)
{
	const ccV3F_C4B_T2F_Quad& quad = sprite->getQuad();
	cocos2d::CCPoint touchLocation = pTouch->getLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	touchLocation = sprite->convertToNodeSpace(touchLocation);
	
	if(isHit(quad, touchLocation))
		return true;
	
	return false;
}

bool isHit(cocos2d::CCSprite* sprite, const cocos2d::CCPoint& pt, int exten_width, int exten_height)
{
    if(pt.x < 0 || pt.y < -exten_height)
		return false;
	if(pt.x > sprite->getContentSize().width + exten_width  || pt.y > sprite->getContentSize().height + exten_height)
		return false;
    
	return true;
}
//for CCScale9Sprite, the local point is based 0,0 in the left bottom.
bool isHit(cocos2d::extension::CCScale9Sprite* sprite, const cocos2d::CCPoint& pt)
{
    if(pt.x < 0 || pt.y < 0)
		return false;
	if(pt.x > sprite->getContentSize().width || pt.y > sprite->getContentSize().height)
		return false;
		
	return true;

}

bool isHit(const cocos2d::ccV3F_C4B_T2F_Quad& quad, const cocos2d::CCPoint& pt)
{
	if(pt.x < quad.bl.vertices.x)
		return false;
	if(pt.x > quad.br.vertices.x)
		return false;
	if(pt.y < quad.bl.vertices.y)
		return false;
	if(pt.y > quad.tl.vertices.y)
		return false;
	
	return true;
}

bool isHit(const cocos2d::CCRect& rect, const cocos2d::CCPoint& pt)
{
	if(pt.x < rect.origin.x)
		return false;
	if(pt.x > rect.origin.x + rect.size.width)
		return false;
	if(pt.y < rect.origin.y)
		return false;
	if(pt.y > rect.origin.y + rect.size.height)
		return false;
	
	return true;
}

void split(std::string src, const char* token, StringVector& vect)
{
    int nend=0;
    int nbegin=0;
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + strlen(token);
    }
}

bool isPointInRect(const cocos2d::CCPoint& pos, const cocos2d::CCRect& rect)
{
	if(pos.x > rect.origin.x && pos.y > rect.origin.y && (pos.x < rect.origin.x + rect.size.width) && (pos.y < rect.origin.y + rect.size.height))
	   return true;
	   
	return false;
}



void addAnimationFiles(const std::string& name)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(getSpriteFrameResourceFullPath(name+".plist").c_str());
}

void addAnimationFrames(CCArray* frames, int startIndex, int endIndex, const std::string& prestr, const std::string& suffixstr)
{
	for(int i = startIndex; i < endIndex; i++)
	{
		std::stringstream ss;
		ss << prestr << std::setfill('0') << std::setw(4) << i << suffixstr;
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ss.str().c_str());
		frames->addObject(frame);
	}	
}


CCParticleSystemQuad* createParticle(const std::string &particle, const cocos2d::CCPoint &pos)
{
	CCParticleSystemQuad* pa = CCParticleSystemQuad::create(particle.c_str());
	pa->setPosition(pos);
	pa->setDuration(-1);
	pa->setPositionType(kCCPositionTypeRelative);
	
	return pa;
}

int getRandomPercentage()
{
	srand(time(NULL));
	return rand() % 100 + 1;
}

//Read UI Layout
CCSize getCurrentResolution()
{
	return CCDirector::sharedDirector()->getWinSize();
}

std::string getUIResourceFullPath(const std::string& file)
{
	return CCFileUtils::sharedFileUtils()->fullPathForFilename(file.c_str());
}
std::string getMD2ResourceFullPath(const std::string& file)
{
	return CCFileUtils::sharedFileUtils()->fullPathForFilename(file.c_str());
}

std::string getAnimationResourceFullPath(const std::string& file)
{
	return CCFileUtils::sharedFileUtils()->fullPathForFilename(file.c_str());
}

std::string getSpriteFrameResourceFullPath(const std::string& file)
{
	return CCFileUtils::sharedFileUtils()->fullPathForFilename(file.c_str());
}

void readPublicPropertys(const CSJson::Value& value, CCNode* node, cocos2d::CCPoint offset)
{
	int alignment = value["alignment"].asInt();
	float posx = value["posX"].asFloat();
	float posy = value["posY"].asFloat();
	CCPoint pos;
	switch (alignment)
	{
		case 0:
		{
			pos.x = posx;
			pos.y = posy;
		}
			break;
		case 1:
		{
			CCSize size = getCurrentResolution();
			pos.x = posx;
			pos.y = size.height - posy;
		}
			break;
		case 2:
		{
			CCSize size = getCurrentResolution();
			pos.x = size.width - posx;
			pos.y = size.height - posy;
		}
			break;
		case 3:
		{
			CCSize size = getCurrentResolution();
			pos.x = size.width - posx;
			pos.y = posy;
		}
			break;
		default:
			break;
	}
	node->setPosition(ccpAdd(pos,offset));
	
	if(!value["tag"].isNull())
	{
		int tag = value["tag"].asInt();
		node->setTag(tag);
	}

	
	float scalex = value["scaleX"].asFloat();
	float scaley = value["scaleY"].asFloat();
	node->setScaleX(scalex);
	node->setScaleY(scaley);
	
	if(!value["rotation"].isNull())
	{
		float rotate = value["rotation"].asFloat();
		node->setRotation(rotate);
	}
}

void readSpriteProperty(const CSJson::Value& value, CCNode* parent, cocos2d::CCPoint offset)
{
	std::string imagename = value["image"].asString();
	CCSprite* sprite = CCSprite::create(getUIResourceFullPath(imagename).c_str());
	
	readPublicPropertys(value, sprite, offset);
	
	if(!value["flipX"].isNull())
	{
		sprite->setFlipX(value["flipX"].asBool());
		sprite->setFlipY(value["flipY"].asBool());
	}
	
	parent->addChild(sprite);
}

void readScale9SpriteProperty(const CSJson::Value& value, CCNode* parent, cocos2d::CCPoint offset)
{
	std::string imagename = value["image"].asString();
	cocos2d::extension::CCScale9Sprite * sprite = cocos2d::extension::CCScale9Sprite::create(getUIResourceFullPath(imagename).c_str());
	
	readPublicPropertys(value, sprite, offset);
	
	float preferedSizeX = value["preferedSizeX"].asFloat();
	float preferedSizeY = value["preferedSizeY"].asFloat();
	sprite->setPreferredSize(CCSizeMake(preferedSizeX, preferedSizeY));
	
	parent->addChild(sprite);
}

void readLabelTTFProperty(const CSJson::Value& value, CCNode* parent, cocos2d::CCPoint offset)
{
	std::string str = value["string"].asString();
	std::string fontName = value["fontName"].asString();
	int fontSize = value["fontSize"].asInt();
	int verticalAlignment = value["verticalAlignment"].asInt();
	int horiAlignment = value["horizontalAlignment"].asInt();
	
	float dimensionX = value["dimensionsX"].asFloat();
	float dimensionY = value["dimensionsY"].asFloat();
	
	CCLabelTTF* label = CCLabelTTF::create(str.c_str(), fontName.c_str(), fontSize, CCSizeMake(dimensionX, dimensionY), (CCTextAlignment)horiAlignment, (CCVerticalTextAlignment)verticalAlignment);
	
	readPublicPropertys(value, label, offset);

	if(!value["colorR"].isNull())
	{
		int colorR = value["colorR"].asInt();
		int colorG = value["colorG"].asInt();
		int colorB = value["colorB"].asInt();
		
		label->setColor(ccc3(colorR, colorG, colorB));
	}

	parent->addChild(label);
}


bool readLayout(cocos2d::CCNode* parent, const std::string& layoutFileName, cocos2d::CCPoint offset)
{
	CSJson::Reader reader;
	CSJson::Value root;
	
	std::string fullpath = getUIResourceFullPath(layoutFileName);
	unsigned char* pBuffer = NULL;
    unsigned long bufferSize = 0;
    
    pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullpath.c_str(), "r", &bufferSize);
    
	std::stringstream in;
    in << pBuffer;
    delete pBuffer;
    pBuffer = NULL;
	
	if (!reader.parse(in.str(), root))
	{
		return false;
	}
	
	for (int i = 0; i < root.size(); i++)
	{
		CSJson::Value value = root[i];
		
		std::string classname = value["class"].asString();
		if (classname == "CCScale9Sprite")
		{
			readScale9SpriteProperty(value, parent, offset);
		}
		else if(classname == "CCSprite")
		{
			readSpriteProperty(value, parent, offset);
		}
		else if(classname == "CCLabelTTF")
		{
			readLabelTTFProperty(value, parent, offset);
		}
	}
	
	return true;
}

CCNode* createNodeFromLayout(const std::string& layoutFileName, cocos2d::CCPoint offset)
{
	CCNode* node = CCNode::create();
	
	if(!readLayout(node, layoutFileName, offset))
	{
		return NULL;
	}
		
	return node;
}

const char* getResolutionPath()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	if (winsize.width < 1500)
	{
		return "960X640/";
	}
	else
	{
		return "1920X1080/";
	}
}

bool isHighResolution()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	return winsize.width >= 1500;
}

float getResolutionScale()
{
	if(isHighResolution())
		return 1;
	else
		return 0.645;
}

void readJsonFile(const std::string& filename, CSJson::Value& root)
{
	CSJson::Reader reader;
	
	unsigned char* pBuffer = NULL;
    unsigned long bufferSize = 0;
    
    pBuffer = CCFileUtils::sharedFileUtils()->getFileData(filename.c_str(), "r", &bufferSize);
    
	std::stringstream in;
    in << pBuffer;
    delete pBuffer;
    pBuffer = NULL;
	
	if (!reader.parse(in.str(), root))
	{
		return;
	}
}
