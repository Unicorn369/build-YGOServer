#ifndef GAME_H
#define GAME_H

#include "config.h"
#ifndef YGOPRO_SERVER_MODE
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else //__APPLE__
#include <GL/gl.h>
#include <GL/glu.h>
#endif //__APPLE__
#include "CGUIImageButton.h"
#include "CGUITTFont.h"
#include "mysignal.h"
#include "client_field.h"
#include "deck_con.h"
#include "menu_handler.h"
#include <ctime>
#else
#include "netserver.h"
#endif //YGOPRO_SERVER_MODE
#include <unordered_map>
#include <vector>
#include <list>
#include <mutex>
#include <functional>

#ifndef YGOPRO_DEFAULT_DUEL_RULE
#define YGOPRO_DEFAULT_DUEL_RULE			5
#endif

#define DEFAULT_DUEL_RULE YGOPRO_DEFAULT_DUEL_RULE
constexpr int CONFIG_LINE_SIZE = 1024;
constexpr int TEXT_LINE_SIZE = 256;

namespace ygo {

template<size_t N>
bool IsExtension(const wchar_t* filename, const wchar_t(&extension)[N]) {
	auto flen = std::wcslen(filename);
	constexpr size_t elen = N - 1;
	if (!elen || flen < elen)
		return false;
	return !mywcsncasecmp(filename + (flen - elen), extension, elen);
}

template<size_t N>
bool IsExtension(const char* filename, const char(&extension)[N]) {
	auto flen = std::strlen(filename);
	constexpr size_t elen = N - 1;
	if (!elen || flen < elen)
		return false;
	return !mystrncasecmp(filename + (flen - elen), extension, elen);
}

#ifndef YGOPRO_SERVER_MODE
struct Config {
	bool use_d3d{ false };
	bool use_image_scale{ true };
	bool use_image_scale_multi_thread{ true };
#ifdef _OPENMP
	bool use_image_load_background_thread{ false };
#else
	bool use_image_load_background_thread{ true };
#endif
	unsigned short antialias{ 0 };
	unsigned short serverport{ 7911 };
	unsigned char textfontsize{ 14 };
	wchar_t lasthost[100]{};
	wchar_t lastport[10]{};
	wchar_t nickname[20]{};
	wchar_t gamename[20]{};
	wchar_t roompass[20]{};
	//path
	wchar_t lastcategory[256]{};
	wchar_t lastdeck[256]{};
	wchar_t textfont[256]{};
	wchar_t numfont[256]{};
	wchar_t bot_deck_path[256]{};
	//settings
	int chkMAutoPos{ 0 };
	int chkSTAutoPos{ 1 };
	int chkRandomPos{ 0 };
	int chkAutoChain{ 0 };
	int chkWaitChain{ 0 };
	int chkDefaultShowChain{ 0 };
	int chkIgnore1{ 0 };
	int chkIgnore2{ 0 };
	int use_lflist{ 1 };
	int default_lflist{ 0 };
	int default_rule{ DEFAULT_DUEL_RULE };
	int hide_setname{ 0 };
	int hide_hint_button{ 0 };
	int control_mode{ 0 };
	int draw_field_spell{ 1 };
	int separate_clear_button{ 1 };
	int auto_search_limit{ -1 };
	int search_multiple_keywords{ 1 };
	int chkIgnoreDeckChanges{ 0 };
	int defaultOT{ 1 };
	int enable_bot_mode{ 0 };
	int quick_animation{ 0 };
	int auto_save_replay{ 0 };
	int draw_single_chain{ 0 };
	int hide_player_name{ 0 };
	int prefer_expansion_script{ 0 };
	bool enable_sound{ true };
	bool enable_music{ true };
	double sound_volume{ 0.5 };
	double music_volume{ 0.5 };
	int music_mode{ 1 };
	bool window_maximized{ false };
	int window_width{ 1024 };
	int window_height{ 640 };
	bool resize_popup_menu{ false };
};

struct DuelInfo {
	bool isStarted{ false };
	bool isInDuel{ false };
	bool isFinished{false};
	bool isReplay{ false };
	bool isReplaySkiping{ false };
	bool isFirst{ false };
	bool isTag{ false };
	bool isSingleMode{ false };
	bool is_shuffling{ false };
	bool tag_player[2]{};
	bool isReplaySwapped{ false };
	int lp[2]{};
	int start_lp{ 0 };
	int duel_rule{ 0 };
	int turn{ 0 };
	short curMsg{ 0 };
	wchar_t hostname[20]{};
	wchar_t clientname[20]{};
	wchar_t hostname_tag[20]{};
	wchar_t clientname_tag[20]{};
	wchar_t strLP[2][16]{};
	std::wstring vic_string;
	unsigned char player_type{ 0 };
	unsigned char time_player{ 0 };
	unsigned short time_limit{ 0 };
	unsigned short time_left[2]{};

	void Clear();
};

struct BotInfo {
	wchar_t name[256]{};
	wchar_t command[256]{};
	wchar_t desc[256]{};
	bool support_master_rule_3{ false };
	bool support_new_master_rule{ false };
	bool support_master_rule_2020{ false };
	bool select_deckfile{ false };
};

struct FadingUnit {
	bool signalAction;
	bool isFadein;
	int fadingFrame;
	int autoFadeoutFrame;
	irr::gui::IGUIElement* guiFading;
	irr::core::recti fadingSize;
	irr::core::vector2di fadingUL;
	irr::core::vector2di fadingLR;
	irr::core::vector2di fadingDiff;
};
#endif //YGOPRO_SERVER_MODE

class Game {

public:
	bool Initialize();
#ifdef YGOPRO_SERVER_MODE
	void MainServerLoop();
	void LoadExpansions();
	void AddDebugMsg(const char* msgbuf);
#else
	void MainLoop();
	void BuildProjectionMatrix(irr::core::matrix4& mProjection, irr::f32 left, irr::f32 right, irr::f32 bottom, irr::f32 top, irr::f32 znear, irr::f32 zfar);
	void InitStaticText(irr::gui::IGUIStaticText* pControl, irr::u32 cWidth, irr::u32 cHeight, irr::gui::CGUITTFont* font, const wchar_t* text);
	std::wstring SetStaticText(irr::gui::IGUIStaticText* pControl, irr::u32 cWidth, irr::gui::CGUITTFont* font, const wchar_t* text, irr::u32 pos = 0);
	void LoadExpansions();
	void RefreshCategoryDeck(irr::gui::IGUIComboBox* cbCategory, irr::gui::IGUIComboBox* cbDeck, bool selectlastused = true);
	void RefreshDeck(irr::gui::IGUIComboBox* cbCategory, irr::gui::IGUIComboBox* cbDeck);
	void RefreshDeck(const wchar_t* deckpath, const std::function<void(const wchar_t*)>& additem);
	void RefreshReplay();
	void RefreshSingleplay();
	void RefreshBot();
	void DrawSelectionLine(irr::video::S3DVertex* vec, bool strip, int width, float* cv);
	void DrawSelectionLine(irr::gui::IGUIElement* element, int width, irr::video::SColor color);
	void DrawBackGround();
	void DrawLinkedZones(ClientCard* pcard);
	void CheckMutual(ClientCard* pcard, int mark);
	void DrawCards();
	void DrawCard(ClientCard* pcard);
	void DrawMisc();
	void DrawStatus(ClientCard* pcard, int x1, int y1, int x2, int y2);
	void DrawGUI();
	void DrawSpec();
	void DrawBackImage(irr::video::ITexture* texture);
	void ShowElement(irr::gui::IGUIElement* element, int autoframe = 0);
	void HideElement(irr::gui::IGUIElement* element, bool set_action = false);
	void PopupElement(irr::gui::IGUIElement* element, int hideframe = 0);
	void WaitFrameSignal(int frame);
	void DrawThumb(code_pointer cp, irr::core::vector2di pos, const LFList* lflist, bool drag = false);
	void DrawDeckBd();
	void LoadConfig();
	void SaveConfig();
	void ShowCardInfo(int code, bool resize = false);
	void ClearCardInfo(int player = 0);
	void AddLog(const wchar_t* msg, int param = 0);
	void AddChatMsg(const wchar_t* msg, int player, bool play_sound = false);
	void ClearChatMsg();
	void AddDebugMsg(const char* msgbuf);
	void ErrorLog(const char* msgbuf);
	void ClearTextures();
	void CloseGameButtons();
	void CloseGameWindow();
	void CloseDuelWindow();

	int LocalPlayer(int player) const;
	int OppositePlayer(int player);
	int ChatLocalPlayer(int player);
	const wchar_t* LocalName(int local_player);

	bool HasFocus(irr::gui::EGUI_ELEMENT_TYPE type) const {
		irr::gui::IGUIElement* focus = env->getFocus();
		return focus && focus->hasType(type);
	}

	void TrimText(irr::gui::IGUIElement* editbox) const {
		irr::core::stringw text(editbox->getText());
		text.trim();
		editbox->setText(text.c_str());
	}

	void OnResize();
	void ResizeChatInputWindow();
	irr::core::recti Resize(irr::s32 x, irr::s32 y, irr::s32 x2, irr::s32 y2);
	irr::core::recti Resize(irr::s32 x, irr::s32 y, irr::s32 x2, irr::s32 y2, irr::s32 dx, irr::s32 dy, irr::s32 dx2, irr::s32 dy2);
	irr::core::vector2di Resize(irr::s32 x, irr::s32 y);
	irr::core::vector2di ResizeReverse(irr::s32 x, irr::s32 y);
	irr::core::recti ResizePhaseHint(irr::s32 x, irr::s32 y, irr::s32 x2, irr::s32 y2, irr::s32 width);
	irr::core::recti ResizeWin(irr::s32 x, irr::s32 y, irr::s32 x2, irr::s32 y2);
	irr::core::recti ResizeCardImgWin(irr::s32 x, irr::s32 y, irr::s32 mx, irr::s32 my);
	irr::core::recti ResizeCardHint(irr::s32 x, irr::s32 y, irr::s32 x2, irr::s32 y2);
	irr::core::vector2di ResizeCardHint(irr::s32 x, irr::s32 y);
	irr::core::recti ResizeCardMid(irr::s32 x, irr::s32 y, irr::s32 x2, irr::s32 y2, irr::s32 midx, irr::s32 midy);
	irr::core::vector2di ResizeCardMid(irr::s32 x, irr::s32 y, irr::s32 midx, irr::s32 midy);
	irr::core::recti ResizeFit(irr::s32 x, irr::s32 y, irr::s32 x2, irr::s32 y2);

	void SetWindowsIcon();
	void SetWindowsScale(float scale);
	void FlashWindow();
	void SetCursor(irr::gui::ECURSOR_ICON icon);
	template<typename T>
	static void DrawShadowText(irr::gui::CGUITTFont* font, const T& text, const irr::core::rect<irr::s32>& position, const irr::core::rect<irr::s32>& padding,
		irr::video::SColor color = 0xffffffff, irr::video::SColor shadowcolor = 0xff000000, bool hcenter = false, bool vcenter = false, const irr::core::rect<irr::s32>* clip = nullptr);

	std::mutex gMutex;
	Signal frameSignal;
	Signal actionSignal;
	Signal replaySignal;
	Signal singleSignal;
	Signal closeSignal;
	Signal closeDoneSignal;
	Config gameConf;
	DuelInfo dInfo;

	std::list<FadingUnit> fadingList;
	std::vector<int> logParam;
	std::wstring chatMsg[8];
	std::vector<BotInfo> botInfo;

	int hideChatTimer{};
	bool hideChat{};
	int chatTiming[8]{};
	int chatType[8]{};
	unsigned short linePatternD3D{};
	unsigned short linePatternGL{ 0x0f0f };
	int waitFrame{};
	int signalFrame{};
	int actionParam{};
	int showingcode{};
	const wchar_t* showingtext{};
	int showcard{};
	int showcardcode{};
	int showcarddif{};
	int showcardp{};
	int is_attacking{};
	int attack_sv{};
	irr::core::vector3df atk_r;
	irr::core::vector3df atk_t;
	float atkdy{};
	int lpframe{};
	int lpd{};
	int lpplayer{};
	int lpccolor{};
	std::wstring lpcstring;
	bool always_chain{};
	bool ignore_chain{};
	bool chain_when_avail{};

	bool is_building{};
	bool is_siding{};

	irr::core::dimension2d<irr::u32> window_size;
	float xScale{ 1.0f };
	float yScale{ 1.0f };

	ClientField dField;
	DeckBuilder deckBuilder;
	MenuHandler menuHandler;
	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver* driver;
	irr::scene::ISceneManager* smgr;
	irr::scene::ICameraSceneNode* camera;

#ifdef _WIN32
	HWND hWnd;
#endif

	//GUI
	irr::gui::IGUIEnvironment* env;
	irr::gui::CGUITTFont* guiFont;
	irr::gui::CGUITTFont* textFont;
	irr::gui::CGUITTFont* numFont;
	irr::gui::CGUITTFont* adFont;
	irr::gui::CGUITTFont* lpcFont;
	std::unordered_map<irr::gui::CGUIImageButton*, int> imageLoading;
	//card image
	irr::gui::IGUIStaticText* wCardImg;
	irr::gui::IGUIImage* imgCard;
	//hint text
	irr::gui::IGUIStaticText* stHintMsg;
	irr::gui::IGUIStaticText* stTip;
	irr::gui::IGUIStaticText* stCardListTip;
	//infos
	irr::gui::IGUITabControl* wInfos;
	irr::gui::IGUIStaticText* stName;
	irr::gui::IGUIStaticText* stInfo;
	irr::gui::IGUIStaticText* stDataInfo;
	irr::gui::IGUIStaticText* stSetName;
	irr::gui::IGUIStaticText* stText;
	irr::gui::IGUIScrollBar* scrCardText;
	irr::gui::IGUIListBox* lstLog;
	irr::gui::IGUIButton* btnClearLog;
	irr::gui::IGUIButton* btnSaveLog;
	irr::gui::IGUIWindow* tabHelper;
	irr::gui::IGUIElement* elmTabHelperLast;
	irr::gui::IGUIScrollBar* scrTabHelper;
	irr::gui::IGUICheckBox* chkMAutoPos;
	irr::gui::IGUICheckBox* chkSTAutoPos;
	irr::gui::IGUICheckBox* chkRandomPos;
	irr::gui::IGUICheckBox* chkAutoChain;
	irr::gui::IGUICheckBox* chkWaitChain;
	irr::gui::IGUICheckBox* chkDefaultShowChain;
	irr::gui::IGUICheckBox* chkQuickAnimation;
	irr::gui::IGUICheckBox* chkAutoSaveReplay;
	irr::gui::IGUICheckBox* chkDrawSingleChain;
	irr::gui::IGUICheckBox* chkHidePlayerName;
	irr::gui::IGUIWindow* tabSystem;
	irr::gui::IGUIElement* elmTabSystemLast;
	irr::gui::IGUIScrollBar* scrTabSystem;
	irr::gui::IGUICheckBox* chkIgnoreDeckChanges;
	irr::gui::IGUICheckBox* chkAutoSearch;
	irr::gui::IGUICheckBox* chkMultiKeywords;
	irr::gui::IGUICheckBox* chkPreferExpansionScript;
	irr::gui::IGUICheckBox* chkLFlist;
	irr::gui::IGUIComboBox* cbLFlist;
	irr::gui::IGUICheckBox* chkEnableSound;
	irr::gui::IGUICheckBox* chkEnableMusic;
	irr::gui::IGUIScrollBar* scrSoundVolume;
	irr::gui::IGUIScrollBar* scrMusicVolume;
	irr::gui::IGUICheckBox* chkMusicMode;
	irr::gui::IGUIButton* btnWinResizeS;
	irr::gui::IGUIButton* btnWinResizeM;
	irr::gui::IGUIButton* btnWinResizeL;
	irr::gui::IGUIButton* btnWinResizeXL;
	//main menu
	irr::gui::IGUIWindow* wMainMenu;
	irr::gui::IGUIButton* btnLanMode;
	irr::gui::IGUIButton* btnSingleMode;
	irr::gui::IGUIButton* btnReplayMode;
	irr::gui::IGUIButton* btnTestMode;
	irr::gui::IGUIButton* btnDeckEdit;
	irr::gui::IGUIButton* btnModeExit;
	//lan
	irr::gui::IGUIWindow* wLanWindow;
	irr::gui::IGUIEditBox* ebNickName;
	irr::gui::IGUIListBox* lstHostList;
	irr::gui::IGUIButton* btnLanRefresh;
	irr::gui::IGUIEditBox* ebJoinHost;
	irr::gui::IGUIEditBox* ebJoinPort;
	irr::gui::IGUIEditBox* ebJoinPass;
	irr::gui::IGUIButton* btnJoinHost;
	irr::gui::IGUIButton* btnJoinCancel;
	irr::gui::IGUIButton* btnCreateHost;
	//create host
	irr::gui::IGUIWindow* wCreateHost;
	irr::gui::IGUIComboBox* cbHostLFlist;
	irr::gui::IGUIComboBox* cbMatchMode;
	irr::gui::IGUIComboBox* cbRule;
	irr::gui::IGUIEditBox* ebTimeLimit;
	irr::gui::IGUIEditBox* ebStartLP;
	irr::gui::IGUIEditBox* ebStartHand;
	irr::gui::IGUIEditBox* ebDrawCount;
	irr::gui::IGUIEditBox* ebServerName;
	irr::gui::IGUIEditBox* ebServerPass;
	irr::gui::IGUIComboBox* cbDuelRule;
	irr::gui::IGUICheckBox* chkNoCheckDeck;
	irr::gui::IGUICheckBox* chkNoShuffleDeck;
	irr::gui::IGUIButton* btnHostConfirm;
	irr::gui::IGUIButton* btnHostCancel;
	//host panel
	irr::gui::IGUIWindow* wHostPrepare;
	irr::gui::IGUIButton* btnHostPrepDuelist;
	irr::gui::IGUIButton* btnHostPrepOB;
	irr::gui::IGUIStaticText* stHostPrepDuelist[4];
	irr::gui::IGUICheckBox* chkHostPrepReady[4];
	irr::gui::IGUIButton* btnHostPrepKick[4];
	irr::gui::IGUIComboBox* cbCategorySelect;
	irr::gui::IGUIComboBox* cbDeckSelect;
	irr::gui::IGUIStaticText* stHostPrepRule;
	irr::gui::IGUIStaticText* stHostPrepOB;
	irr::gui::IGUIButton* btnHostPrepReady;
	irr::gui::IGUIButton* btnHostPrepNotReady;
	irr::gui::IGUIButton* btnHostPrepStart;
	irr::gui::IGUIButton* btnHostPrepCancel;
	//replay
	irr::gui::IGUIWindow* wReplay;
	irr::gui::IGUIListBox* lstReplayList;
	irr::gui::IGUIStaticText* stReplayInfo;
	irr::gui::IGUIButton* btnLoadReplay;
	irr::gui::IGUIButton* btnDeleteReplay;
	irr::gui::IGUIButton* btnRenameReplay;
	irr::gui::IGUIButton* btnReplayCancel;
	irr::gui::IGUIButton* btnExportDeck;
	irr::gui::IGUIEditBox* ebRepStartTurn;
	//single play
	irr::gui::IGUIWindow* wSinglePlay;
	irr::gui::IGUIListBox* lstBotList;
	irr::gui::IGUIStaticText* stBotInfo;
	irr::gui::IGUIButton* btnStartBot;
	irr::gui::IGUIButton* btnBotCancel;
	irr::gui::IGUIComboBox* cbBotDeckCategory;
	irr::gui::IGUIComboBox* cbBotDeck;
	irr::gui::IGUIComboBox* cbBotRule;
	irr::gui::IGUICheckBox* chkBotHand;
	irr::gui::IGUICheckBox* chkBotNoCheckDeck;
	irr::gui::IGUICheckBox* chkBotNoShuffleDeck;
	irr::gui::IGUIListBox* lstSinglePlayList;
	irr::gui::IGUIStaticText* stSinglePlayInfo;
	irr::gui::IGUICheckBox* chkSinglePlayReturnDeckTop;
	irr::gui::IGUIButton* btnLoadSinglePlay;
	irr::gui::IGUIButton* btnSinglePlayCancel;
	//hand
	irr::gui::IGUIWindow* wHand;
	irr::gui::IGUIButton* btnHand[3];
	//
	irr::gui::IGUIWindow* wFTSelect;
	irr::gui::IGUIButton* btnFirst;
	irr::gui::IGUIButton* btnSecond;
	//message
	irr::gui::IGUIWindow* wMessage;
	irr::gui::IGUIStaticText* stMessage;
	irr::gui::IGUIButton* btnMsgOK;
	//auto close message
	irr::gui::IGUIWindow* wACMessage;
	irr::gui::IGUIStaticText* stACMessage;
	//yes/no
	irr::gui::IGUIWindow* wQuery;
	irr::gui::IGUIStaticText* stQMessage;
	irr::gui::IGUIButton* btnYes;
	irr::gui::IGUIButton* btnNo;
	//surrender yes/no
	irr::gui::IGUIWindow* wSurrender;
	irr::gui::IGUIStaticText* stSurrenderMessage;
	irr::gui::IGUIButton* btnSurrenderYes;
	irr::gui::IGUIButton* btnSurrenderNo;
	//options
	irr::gui::IGUIWindow* wOptions;
	irr::gui::IGUIStaticText* stOptions;
	irr::gui::IGUIButton* btnOptionp;
	irr::gui::IGUIButton* btnOptionn;
	irr::gui::IGUIButton* btnOptionOK;
	irr::gui::IGUIButton* btnOption[5];
	irr::gui::IGUIScrollBar* scrOption;
	//pos selection
	irr::gui::IGUIWindow* wPosSelect;
	irr::gui::CGUIImageButton* btnPSAU;
	irr::gui::CGUIImageButton* btnPSAD;
	irr::gui::CGUIImageButton* btnPSDU;
	irr::gui::CGUIImageButton* btnPSDD;
	//card selection
	irr::gui::IGUIWindow* wCardSelect;
	irr::gui::CGUIImageButton* btnCardSelect[5];
	irr::gui::IGUIStaticText *stCardPos[5];
	irr::gui::IGUIScrollBar *scrCardList;
	irr::gui::IGUIButton* btnSelectOK;
	//card display
	irr::gui::IGUIWindow* wCardDisplay;
	irr::gui::CGUIImageButton* btnCardDisplay[5];
	irr::gui::IGUIStaticText *stDisplayPos[5];
	irr::gui::IGUIScrollBar *scrDisplayList;
	irr::gui::IGUIButton* btnDisplayOK;
	//announce number
	irr::gui::IGUIWindow* wANNumber;
	irr::gui::IGUIComboBox* cbANNumber;
	irr::gui::IGUIButton* btnANNumber[12];
	irr::gui::IGUIButton* btnANNumberOK;
	//announce card
	irr::gui::IGUIWindow* wANCard;
	irr::gui::IGUIEditBox* ebANCard;
	irr::gui::IGUIListBox* lstANCard;
	irr::gui::IGUIButton* btnANCardOK;
	//announce attribute
	irr::gui::IGUIWindow* wANAttribute;
	irr::gui::IGUICheckBox* chkAttribute[7];
	//announce race
	irr::gui::IGUIWindow* wANRace;
	irr::gui::IGUICheckBox* chkRace[RACES_COUNT];
	//cmd menu
	irr::gui::IGUIWindow* wCmdMenu;
	irr::gui::IGUIButton* btnActivate;
	irr::gui::IGUIButton* btnSummon;
	irr::gui::IGUIButton* btnSPSummon;
	irr::gui::IGUIButton* btnMSet;
	irr::gui::IGUIButton* btnSSet;
	irr::gui::IGUIButton* btnRepos;
	irr::gui::IGUIButton* btnAttack;
	irr::gui::IGUIButton* btnShowList;
	irr::gui::IGUIButton* btnOperation;
	irr::gui::IGUIButton* btnReset;
	irr::gui::IGUIButton* btnShuffle;
	//chat window
	irr::gui::IGUIWindow* wChat;
	irr::gui::IGUIListBox* lstChatLog;
	irr::gui::IGUIEditBox* ebChatInput;
	irr::gui::IGUICheckBox* chkIgnore1;
	irr::gui::IGUICheckBox* chkIgnore2;
	//phase button
	irr::gui::IGUIStaticText* wPhase;
	irr::gui::IGUIButton* btnPhaseStatus;
	irr::gui::IGUIButton* btnBP;
	irr::gui::IGUIButton* btnM2;
	irr::gui::IGUIButton* btnEP;
	//deck edit
	irr::gui::IGUIStaticText* wDeckEdit;
	irr::gui::IGUIComboBox* cbDBCategory;
	irr::gui::IGUIComboBox* cbDBDecks;
	irr::gui::IGUIButton* btnManageDeck;
	irr::gui::IGUIButton* btnClearDeck;
	irr::gui::IGUIButton* btnSortDeck;
	irr::gui::IGUIButton* btnShuffleDeck;
	irr::gui::IGUIButton* btnSaveDeck;
	irr::gui::IGUIButton* btnDeleteDeck;
	irr::gui::IGUIButton* btnSaveDeckAs;
	irr::gui::IGUIButton* btnSideOK;
	irr::gui::IGUIButton* btnSideShuffle;
	irr::gui::IGUIButton* btnSideSort;
	irr::gui::IGUIButton* btnSideReload;
	irr::gui::IGUIEditBox* ebDeckname;
	irr::gui::IGUIStaticText* stDBCategory;
	irr::gui::IGUIStaticText* stDeck;
	irr::gui::IGUIStaticText* stCategory;
	irr::gui::IGUIStaticText* stLimit;
	irr::gui::IGUIStaticText* stAttribute;
	irr::gui::IGUIStaticText* stRace;
	irr::gui::IGUIStaticText* stAttack;
	irr::gui::IGUIStaticText* stDefense;
	irr::gui::IGUIStaticText* stStar;
	irr::gui::IGUIStaticText* stSearch;
	irr::gui::IGUIStaticText* stScale;
	//deck manage
	irr::gui::IGUIWindow* wDeckManage;
	irr::gui::IGUIListBox* lstCategories;
	irr::gui::IGUIListBox* lstDecks;
	irr::gui::IGUIButton* btnNewCategory;
	irr::gui::IGUIButton* btnRenameCategory;
	irr::gui::IGUIButton* btnDeleteCategory;
	irr::gui::IGUIButton* btnNewDeck;
	irr::gui::IGUIButton* btnRenameDeck;
	irr::gui::IGUIButton* btnDMDeleteDeck;
	irr::gui::IGUIButton* btnMoveDeck;
	irr::gui::IGUIButton* btnCopyDeck;
	irr::gui::IGUIButton* btnImportDeckCode;
	irr::gui::IGUIButton* btnExportDeckCode;
	irr::gui::IGUIWindow* wDMQuery;
	irr::gui::IGUIStaticText* stDMMessage;
	irr::gui::IGUIStaticText* stDMMessage2;
	irr::gui::IGUIEditBox* ebDMName;
	irr::gui::IGUIComboBox* cbDMCategory;
	irr::gui::IGUIButton* btnDMOK;
	irr::gui::IGUIButton* btnDMCancel;
	irr::gui::IGUIScrollBar* scrPackCards;
	//filter
	irr::gui::IGUIStaticText* wFilter;
	irr::gui::IGUIScrollBar* scrFilter;
	irr::gui::IGUIComboBox* cbCardType;
	irr::gui::IGUIComboBox* cbCardType2;
	irr::gui::IGUIComboBox* cbRace;
	irr::gui::IGUIComboBox* cbAttribute;
	irr::gui::IGUIComboBox* cbLimit;
	irr::gui::IGUIEditBox* ebStar;
	irr::gui::IGUIEditBox* ebScale;
	irr::gui::IGUIEditBox* ebAttack;
	irr::gui::IGUIEditBox* ebDefense;
	irr::gui::IGUIEditBox* ebCardName;
	irr::gui::IGUIButton* btnEffectFilter;
	irr::gui::IGUIButton* btnStartFilter;
	irr::gui::IGUIButton* btnClearFilter;
	irr::gui::IGUIWindow* wCategories;
	irr::gui::IGUICheckBox* chkCategory[32];
	irr::gui::IGUIButton* btnCategoryOK;
	irr::gui::IGUIButton* btnMarksFilter;
	irr::gui::IGUIWindow* wLinkMarks;
	irr::gui::IGUIButton* btnMark[8];
	irr::gui::IGUIButton* btnMarksOK;
	//sort type
	irr::gui::IGUIStaticText* wSort;
	irr::gui::IGUIComboBox* cbSortType;
	//replay save
	irr::gui::IGUIWindow* wReplaySave;
	irr::gui::IGUIEditBox* ebRSName;
	irr::gui::IGUIButton* btnRSYes;
	irr::gui::IGUIButton* btnRSNo;
	//replay control
	irr::gui::IGUIStaticText* wReplayControl;
	irr::gui::IGUIButton* btnReplayStart;
	irr::gui::IGUIButton* btnReplayPause;
	irr::gui::IGUIButton* btnReplayStep;
	irr::gui::IGUIButton* btnReplayUndo;
	irr::gui::IGUIButton* btnReplayExit;
	irr::gui::IGUIButton* btnReplaySwap;
	//surrender/leave
	irr::gui::IGUIButton* btnLeaveGame;
	//swap
	irr::gui::IGUIButton* btnSpectatorSwap;
	//chain control
	irr::gui::IGUIButton* btnChainIgnore;
	irr::gui::IGUIButton* btnChainAlways;
	irr::gui::IGUIButton* btnChainWhenAvail;
	//cancel or finish
	irr::gui::IGUIButton* btnCancelOrFinish;
	//big picture
	irr::gui::IGUIWindow* wBigCard;
	irr::gui::IGUIImage* imgBigCard;
	irr::gui::IGUIButton* btnBigCardOriginalSize;
	irr::gui::IGUIButton* btnBigCardZoomIn;
	irr::gui::IGUIButton* btnBigCardZoomOut;
	irr::gui::IGUIButton* btnBigCardClose;
#endif //YGOPRO_SERVER_MODE
};

extern Game* mainGame;

#ifdef YGOPRO_SERVER_MODE
#define MAX_MATCH_COUNT 3

extern unsigned short server_port;
extern unsigned short replay_mode;
extern HostInfo game_info;
extern uint32_t pre_seed[MAX_MATCH_COUNT][SEED_COUNT];
extern uint8_t pre_seed_specified[MAX_MATCH_COUNT];
#endif
}

#ifdef YGOPRO_SERVER_MODE
#define SIZE_QUERY_BUFFER	0x40000
#else
#define SIZE_QUERY_BUFFER	0x4000
#endif

#define CARD_IMG_WIDTH		177
#define CARD_IMG_HEIGHT		254
#define CARD_THUMB_WIDTH	44
#define CARD_THUMB_HEIGHT	64

#define UEVENT_EXIT			0x1
#define UEVENT_TOWINDOW		0x2

#define COMMAND_ACTIVATE	0x0001
#define COMMAND_SUMMON		0x0002
#define COMMAND_SPSUMMON	0x0004
#define COMMAND_MSET		0x0008
#define COMMAND_SSET		0x0010
#define COMMAND_REPOS		0x0020
#define COMMAND_ATTACK		0x0040
#define COMMAND_LIST		0x0080
#define COMMAND_OPERATION	0x0100
#define COMMAND_RESET		0x0200

#define POSITION_HINT		0x8000

#define BUTTON_LAN_MODE				100
#define BUTTON_SINGLE_MODE			101
#define BUTTON_REPLAY_MODE			102
#define BUTTON_TEST_MODE			103
#define BUTTON_DECK_EDIT			104
#define BUTTON_MODE_EXIT			105
#define LISTBOX_LAN_HOST			110
#define BUTTON_JOIN_HOST			111
#define BUTTON_JOIN_CANCEL			112
#define BUTTON_CREATE_HOST			113
#define BUTTON_HOST_CONFIRM			114
#define BUTTON_HOST_CANCEL			115
#define BUTTON_LAN_REFRESH			116
#define BUTTON_HP_DUELIST			120
#define BUTTON_HP_OBSERVER			121
#define BUTTON_HP_START				122
#define BUTTON_HP_CANCEL			123
#define BUTTON_HP_KICK				124
#define CHECKBOX_HP_READY			125
#define BUTTON_HP_READY				126
#define BUTTON_HP_NOTREADY			127
#define COMBOBOX_HP_CATEGORY		128
#define LISTBOX_REPLAY_LIST			130
#define BUTTON_LOAD_REPLAY			131
#define BUTTON_CANCEL_REPLAY		132
#define BUTTON_DELETE_REPLAY		133
#define BUTTON_RENAME_REPLAY		134
#define BUTTON_EXPORT_DECK			135
#define BUTTON_REPLAY_START			140
#define BUTTON_REPLAY_PAUSE			141
#define BUTTON_REPLAY_STEP			142
#define BUTTON_REPLAY_UNDO			143
#define BUTTON_REPLAY_EXIT			144
#define BUTTON_REPLAY_SWAP			145
#define BUTTON_REPLAY_SAVE			146
#define BUTTON_REPLAY_CANCEL		147
#define LISTBOX_SINGLEPLAY_LIST		150
#define BUTTON_LOAD_SINGLEPLAY		151
#define BUTTON_CANCEL_SINGLEPLAY	152
#define LISTBOX_BOT_LIST			153
#define BUTTON_BOT_START			154
#define COMBOBOX_BOT_RULE			155
#define COMBOBOX_BOT_DECKCATEGORY	156
#define EDITBOX_CHAT				199

#define BUTTON_MSG_OK				200
#define BUTTON_YES					201
#define BUTTON_NO					202
#define BUTTON_HAND1				205
#define BUTTON_HAND2				206
#define BUTTON_HAND3				207
#define BUTTON_FIRST				208
#define BUTTON_SECOND				209
#define BUTTON_POS_AU				210
#define BUTTON_POS_AD				211
#define BUTTON_POS_DU				212
#define BUTTON_POS_DD				213
#define BUTTON_OPTION_PREV			220
#define BUTTON_OPTION_NEXT			221
#define BUTTON_OPTION_OK			222
#define BUTTON_OPTION_0				223
#define BUTTON_OPTION_1				224
#define BUTTON_OPTION_2				225
#define BUTTON_OPTION_3				226
#define BUTTON_OPTION_4				227
#define SCROLL_OPTION_SELECT		228
#define BUTTON_CARD_0				230
#define BUTTON_CARD_1				231
#define BUTTON_CARD_2				232
#define BUTTON_CARD_3				233
#define BUTTON_CARD_4				234
#define SCROLL_CARD_SELECT			235
#define BUTTON_CARD_SEL_OK			236
#define TEXT_CARD_LIST_TIP			237
#define BUTTON_CMD_ACTIVATE			240
#define BUTTON_CMD_SUMMON			241
#define BUTTON_CMD_SPSUMMON			242
#define BUTTON_CMD_MSET				243
#define BUTTON_CMD_SSET				244
#define BUTTON_CMD_REPOS			245
#define BUTTON_CMD_ATTACK			246
#define BUTTON_CMD_SHOWLIST			247
#define BUTTON_CMD_SHUFFLE			248
#define BUTTON_CMD_RESET			249
#define BUTTON_ANNUMBER_OK			250
#define BUTTON_ANCARD_OK			251
#define EDITBOX_ANCARD				252
#define LISTBOX_ANCARD				253
#define CHECK_ATTRIBUTE				254
#define CHECK_RACE					255
#define BUTTON_BP					260
#define BUTTON_M2					261
#define BUTTON_EP					262
#define BUTTON_LEAVE_GAME			263
#define BUTTON_CHAIN_IGNORE			264
#define BUTTON_CHAIN_ALWAYS			265
#define BUTTON_CHAIN_WHENAVAIL		266
#define BUTTON_CANCEL_OR_FINISH		267
#define BUTTON_PHASE				268
#define BUTTON_ANNUMBER_1			270
#define BUTTON_ANNUMBER_2			271
#define BUTTON_ANNUMBER_3			272
#define BUTTON_ANNUMBER_4			273
#define BUTTON_ANNUMBER_5			274
#define BUTTON_ANNUMBER_6			275
#define BUTTON_ANNUMBER_7			276
#define BUTTON_ANNUMBER_8			277
#define BUTTON_ANNUMBER_9			278
#define BUTTON_ANNUMBER_10			279
#define BUTTON_ANNUMBER_11			280
#define BUTTON_ANNUMBER_12			281
#define BUTTON_DISPLAY_0			290
#define BUTTON_DISPLAY_1			291
#define BUTTON_DISPLAY_2			292
#define BUTTON_DISPLAY_3			293
#define BUTTON_DISPLAY_4			294
#define SCROLL_CARD_DISPLAY			295
#define BUTTON_CARD_DISP_OK			296
#define BUTTON_SURRENDER_YES		297
#define BUTTON_SURRENDER_NO			298

#define BUTTON_MANAGE_DECK			300
#define COMBOBOX_DBCATEGORY			301
#define COMBOBOX_DBDECKS			302
#define BUTTON_CLEAR_DECK			303
#define BUTTON_SAVE_DECK			304
#define BUTTON_SAVE_DECK_AS			305
#define BUTTON_DELETE_DECK			306
#define BUTTON_SIDE_RELOAD			307
#define BUTTON_SORT_DECK			308
#define BUTTON_SIDE_OK				309
#define BUTTON_SHUFFLE_DECK			310
#define COMBOBOX_MAINTYPE			311
#define COMBOBOX_SECONDTYPE			312
#define BUTTON_EFFECT_FILTER		313
#define BUTTON_START_FILTER			314
#define SCROLL_FILTER				315
#define EDITBOX_KEYWORD				316
#define BUTTON_CLEAR_FILTER			317
#define COMBOBOX_ATTRIBUTE			318
#define COMBOBOX_RACE				319
#define COMBOBOX_LIMIT				320
#define BUTTON_CATEGORY_OK			321
#define BUTTON_MARKS_FILTER			322
#define BUTTON_MARKERS_OK			323
#define COMBOBOX_SORTTYPE			324
#define EDITBOX_INPUTS				325
#define WINDOW_DECK_MANAGE			330
#define BUTTON_NEW_CATEGORY			331
#define BUTTON_RENAME_CATEGORY		332
#define BUTTON_DELETE_CATEGORY		333
#define BUTTON_NEW_DECK				334
#define BUTTON_RENAME_DECK			335
#define BUTTON_DELETE_DECK_DM		336
#define BUTTON_MOVE_DECK			337
#define BUTTON_COPY_DECK			338
#define LISTBOX_CATEGORIES			339
#define LISTBOX_DECKS				340
#define BUTTON_DM_OK				341
#define BUTTON_DM_CANCEL			342
#define BUTTON_IMPORT_DECK_CODE		343
#define BUTTON_EXPORT_DECK_CODE		344
#define COMBOBOX_LFLIST				349

#define BUTTON_CLEAR_LOG			350
#define LISTBOX_LOG					351
#define SCROLL_CARDTEXT				352
#define CHECKBOX_AUTO_SEARCH		360
#define CHECKBOX_ENABLE_SOUND		361
#define CHECKBOX_ENABLE_MUSIC		362
#define SCROLL_VOLUME				363
#define CHECKBOX_DISABLE_CHAT		364
#define BUTTON_WINDOW_RESIZE_S		365
#define BUTTON_WINDOW_RESIZE_M		366
#define BUTTON_WINDOW_RESIZE_L		367
#define BUTTON_WINDOW_RESIZE_XL		368
#define CHECKBOX_QUICK_ANIMATION	369
#define SCROLL_TAB_HELPER			370
#define SCROLL_TAB_SYSTEM			371
#define CHECKBOX_MULTI_KEYWORDS		372
#define CHECKBOX_PREFER_EXPANSION	373
#define CHECKBOX_DRAW_SINGLE_CHAIN	374
#define CHECKBOX_LFLIST				375
#define CHECKBOX_HIDE_PLAYER_NAME	376
#define BUTTON_BIG_CARD_CLOSE		380
#define BUTTON_BIG_CARD_ZOOM_IN		381
#define BUTTON_BIG_CARD_ZOOM_OUT	382
#define BUTTON_BIG_CARD_ORIG_SIZE	383

#define AVAIL_OCG					0x1
#define AVAIL_TCG					0x2
#define AVAIL_CUSTOM				0x4
#define AVAIL_SC					0x8
#define AVAIL_OCGTCG				(AVAIL_OCG|AVAIL_TCG)

#define MAX_LAYER_COUNT	6
#endif // GAME_H
