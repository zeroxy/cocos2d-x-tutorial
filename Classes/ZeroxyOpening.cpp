#include "ZeroxyOpening.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* Opening::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Opening::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Opening::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Opening::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width ,
                                origin.y + closeItem->getContentSize().height));
	//closeItem->setScale(2.0f);

    // create menu, it's an autorelease object

    MenuItemFont* menu1 = MenuItemFont::create("Start", CC_CALLBACK_1(Opening::menuStartCallback, this));
    MenuItemFont* menu2 = MenuItemFont::create("highscore", CC_CALLBACK_1(Opening::menuHighscoreCallback, this));

    menu1->setColor(Color3B(255, 0.0f, 0.0f));
    menu1->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/3*2));
    menu2->setColor(Color3B(255, 255, 0.0f));
    menu2->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/3*1));

    auto menu = Menu::create(closeItem, menu1, menu2, NULL );
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(0,0));//visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 4);
    
    auto action = MoveTo::create(7.0, Vec2(visibleSize.width, 0));

    sprite->runAction(action);

    CCSprite *charactorSprite = CCSprite::create();
    charactorSprite->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));

    CCSpriteFrame *sprite_char_ani1 = CCSpriteFrame::create("sma4_sprites-4.png", CCRect(18*1, 18, 18, 29));
    CCSpriteFrame *sprite_char_ani2 = CCSpriteFrame::create("sma4_sprites-4.png", CCRect(18*2, 18, 18, 29));
    CCSpriteFrame *sprite_char_ani3 = CCSpriteFrame::create("sma4_sprites-4.png", CCRect(18*3, 18, 18, 29));
    CCSpriteFrame *sprite_char_ani4 = CCSpriteFrame::create("sma4_sprites-4.png", CCRect(18*4, 18, 18, 29));

    CCAnimation * animation = CCAnimation::create();
    animation->setDelayPerUnit(0.5f);
    animation->addSpriteFrame(sprite_char_ani1);
    animation->addSpriteFrame(sprite_char_ani2);
    animation->addSpriteFrame(sprite_char_ani3);
    animation->addSpriteFrame(sprite_char_ani4);
    animation->setLoops(-1);

    charactorSprite->setScale(20.0f);
    charactorSprite->runAction(CCAnimate::create(animation));
    this->addChild(charactorSprite,3);

    return true;
}

void Opening::menuStartCallback(Ref* pSender){
	CCLog("pushed Start!!!");

	Scene* newScene = HelloWorld::createScene();
	Director::getInstance()->pushScene(newScene);
}
void Opening::menuHighscoreCallback(Ref* pSender){
	CCLog("pushed Highscore!!!");
}
void Opening::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
