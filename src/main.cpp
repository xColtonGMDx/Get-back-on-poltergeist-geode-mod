#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(HiButtonMenuLayer, MenuLayer) {
public:
    bool init() {
        if (!MenuLayer::init())
            return false;

        // Find the title sprite
        auto title = this->getChildByID("main-menu");
        if (!title)
            return true;

        // Load your custom icon (from mod.json resources)
        auto btnSpr = CCSprite::create("icon.png");
        if (!btnSpr) {
            log::error("Failed to load icon.png");
            return true;
        }

        // Create button
        auto btn = CCMenuItemSpriteExtra::create(
            btnSpr,
            this,
            menu_selector(HiButtonMenuLayer::onHiButton)
        );

        // Position it somewhere visible
        btn->setPosition({200, 200});

        // Add to menu
        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition(0, 0);
        this->addChild(menu);

        return true;
    }

    void onHiButton(CCObject*) {
        auto layer = CCLayerColor::create({0, 0, 0, 180});
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // Background (MUST use sprite frame on Android)
        auto bg = CCSprite::createWithSpriteFrameName("GJ_square01.png");
        if (!bg) {
            log::error("Failed to load GJ_square01.png");
            return;
        }
        bg->setScale(2.0f);
        bg->setPosition(winSize / 2);
        layer->addChild(bg);

        // Label (gjFont.fnt DOES NOT EXIST on Android)
        auto label = CCLabelBMFont::create("Get back on poltergeist dumbass", "bigFont.fnt");
        if (!label) {
            log::error("Failed to load bigFont.fnt");
            return;
        }
        label->setPosition(winSize / 2);
        layer->addChild(label);

        // Close button (must use sprite frame)
        auto closeSpr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        if (!closeSpr) {
            log::error("Failed to load GJ_closeBtn_001.png");
            return;
        }

        auto closeBtn = CCMenuItemSpriteExtra::create(
            closeSpr,
            this,
            menu_selector(HiButtonMenuLayer::onClose)
        );

        auto menu = CCMenu::create();
        menu->addChild(closeBtn);
        menu->setPosition(winSize.width / 2 + 120, winSize.height / 2 + 120);
        layer->addChild(menu);

        layer->setTag(999);
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 999);
    }

    void onClose(CCObject*) {
        auto scene = CCDirector::sharedDirector()->getRunningScene();
        scene->removeChildByTag(999);
    }
};
