#ifndef SFSAMP_H__
#define SFSAMP_H__

enum DialogStyle {
	DIALOG_STYLE_MSGBOX = 0,
	DIALOG_STYLE_INPUT = 1,
	DIALOG_STYLE_LIST = 2,
	DIALOG_STYLE_PASSWORD = 3,
	DIALOG_STYLE_TABLIST = 4,
	DIALOG_STYLE_TABLIST_HEADERS = 5
};

enum Gamestate : int {
	GAMESTATE_NONE = 0,
	GAMESTATE_WAIT_CONNECT = 1,
	GAMESTATE_DISCONNECTED = 2,
	GAMESTATE_AWAIT_JOIN = 6,
	GAMESTATE_CONNECTED = 5,
	GAMESTATE_RESTARTING = 11,
};

enum PlayerState : uint8_t {
	PLAYER_STATE_NONE = 0,
	PLAYER_STATE_ONFOOT = 17,
	PLAYER_STATE_PASSENGER = 18,
	PLAYER_STATE_DRIVER = 19,
	PLAYER_STATE_WASTED = 32,
	PLAYER_STATE_SPAWNED = 33
};

enum PlayerStatus : int { 
	PLAYER_STATUS_TIMEOUT = 2,
};

enum UpdateType : uint8_t {
	UPDATE_TYPE_NONE,
	UPDATE_TYPE_ONFOOT = 16,
	UPDATE_TYPE_INCAR = 17,
	UPDATE_TYPE_PASSENGER = 18,
};

enum Limits {
	SAMP_MAX_ACTORS = 1000,
	SAMP_MAX_PLAYERS = 1004,
	SAMP_MAX_VEHICLES = 2000,
	SAMP_MAX_PICKUPS = 4096,
	SAMP_MAX_OBJECTS = 1000,
	SAMP_MAX_GANGZONES = 1024,
	SAMP_MAX_3DTEXTS = 2048,
	SAMP_MAX_TEXTDRAWS = 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_CLIENTCMDS = 144,
	SAMP_MAX_MENUS = 128,
	SAMP_MAX_PLAYER_NAME = 24,
	SAMP_ALLOWED_PLAYER_NAME_LENGTH = 20,
	SAMP_MAX_ACCESSORIES = 10,
};

enum ChatMessageType {
	CHAT_TYPE_NONE = 0,
	CHAT_TYPE_CHAT = 2,
	CHAT_TYPE_INFO = 4,
	CHAT_TYPE_DEBUG = 8
};

enum ChatDisplayMode {
	CHAT_WINDOW_MODE_OFF = 0,
	CHAT_WINDOW_MODE_LIGHT = 1,
	CHAT_WINDOW_MODE_FULL = 2
};

enum SendrateType {
	ONFOOTSENDRATE = 1,
	INCARSENDRATE = 2,
	AIMSENDRATE = 3
};

enum SurfingMode : int {
	SURFING_MODE_NONE,
	SURFING_MODE_UNFIXED,
	SURFING_MODE_FIXED
};

enum SpectatingMode : uint8_t {
	SPECTATING_MODE_VEHICLE = 3,
	SPECTATING_MODE_PLAYER = 4,
	SPECTATING_MODE_FIXED = 15,
	SPECTATING_MODE_SIDE = 14
};

enum SpectatingType : uint8_t {
	SPECTATING_TYPE_NONE = 0,
	SPECTATING_TYPE_PLAYER = 1,
	SPECTATING_TYPE_VEHICLE = 2,
};

enum StuffType : int {
	STUFF_TYPE_NONE,
	STUFF_TYPE_BEER,
	STUFF_TYPE_DYN_BEER,
	STUFF_TYPE_PINT_GLASS,
	STUFF_TYPE_CIGGI
};

typedef enum detour_types_s {
	DETOUR_TYPE_NOT_SET = -1,
	DETOUR_TYPE_JMP,
	DETOUR_TYPE_PUSH_RET,
	DETOUR_TYPE_PUSH_FUNC,
	DETOUR_TYPE_CALL_FUNC,
} detour_types_t;

#pragma pack(push, 1)

// structures
struct SAMPPools {
	struct MenuPool* menuPool;
	struct ActorPool* actorPool;
	struct PlayerPool* playerPool;
	struct VehiclePool* vehiclePool;
	struct PickupPool* pickupPool;
	struct ObjectPool* objectPool;
	struct GangzonePool* gangzonePool;
	struct TextLabelPool* textLabelPool;	
	struct TextdrawPool* textdrawPool;
};

struct SAMPFUNCS_API NetGame {
	char unk[44];
	RakClientInterface* rakClientInterface;
	char serverIp[257];
	char serverName[257];
	bool disableCollision;
	bool updateCameraTarget;
	bool nametagStatus;
	uint32_t serverPort;
	BOOL lanMode;
	uint32_t mapIcons[100];
	Gamestate gameState;
	uint32_t lastConnectAttempt;
	struct ServerPresets* serverPresets;
	char controlLocked;
	int unk2;
	struct SAMPPools* pools;

	void RestartGame(void);
	short GetAnimationIDFromName(char* pszAnimFile, char* pszAnimName);
	char *GetAnimationNameFromID(short sAnimationID);
	void UpdateScoreAndPing(void);
	RPCNode* GetRPCNodeByIndex(uint8_t index);
};

struct ServerPresets {
	bool useCJWalk;
	unsigned int deadDropsMoney;
	float worldBoundaries[4];
	bool allowWeapons;
	float gravity;
	bool disableInteriorEnterExits;
	BOOL vehicleFriendlyFire;
	bool holdTime;
	bool instagib;
	bool zoneNames;
	bool friendlyFire;
	BOOL classesAvailable;
	float nameTagsDrawDistance;
	bool manualVehicleEngineAndLight;
	uint8_t worldTimeHour;
	uint8_t worldTimeMinute;
	uint8_t weatherId;
	bool nametagsBehindWalls;
	int playerMarkersMode;
	float globalChatRadiusLimit;
	bool showNameTags;
	bool ltdChatRadius;
};

struct TextDrawTransmit {
	union {		
		struct {
			uint8_t box : 1;
			uint8_t left : 1;
			uint8_t right : 1;
			uint8_t center : 1;
			uint8_t proportional : 1;
			uint8_t padding : 3;
		};
		uint8_t flags;
	};
	float letterWidth;
	float letterHeight;
	uint32_t letterColor;
	float boxWidth;
	float boxHeight;
	uint32_t boxColor;
	uint8_t shadow;
	uint8_t outline;
	uint32_t backgroundColor;
	uint8_t style;
	uint8_t selectable;
	float position[2];
	uint16_t modelId;
	float modelRotation[3];
	float modelZoom;
	uint16_t color[2];
};

struct Textdraw {
	char text[800 + 1];
	char string[1600 + 2];
	float letterWidth;
	float letterHeight;
	uint32_t letterColor;
	uint8_t unk;
	uint8_t center;
	uint8_t box;
	float boxSize[2];
	uint32_t boxColor;
	uint8_t proportional;
	uint32_t shadowColor;
	uint8_t shadowSize;
	uint8_t outline;
	uint8_t alignLeft;
	uint8_t alignRight;
	int style;		// font style/texture/model
	float position[2];
	uint8_t gxt[8];
	uint32_t param1;	// -1 by default
	uint32_t param2;	// -1 by default
	uint32_t index;		// -1 if bad
	uint8_t selectable;	// = 1; 0 by default
	uint16_t modelId;
	float modelRotation[3];
	float modelZoom;
	uint16_t color[2];
	uint8_t field_9BE;
	uint8_t rectIsReady;
	uint8_t KCodesIsUsed;
	float rect[4];
	uint8_t isHovered;
	uint32_t hoverColor;
};

struct SAMPFUNCS_API TextdrawPool {
	BOOL globalIsListed[SAMP_MAX_TEXTDRAWS];
	BOOL localIsListed[SAMP_MAX_PLAYERTEXTDRAWS];
	struct Textdraw* globalTextdraw[SAMP_MAX_TEXTDRAWS];
	struct Textdraw* localTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];

	Textdraw* Create(uint16_t id, TextDrawTransmit* transmit, char *text);
	void Delete(uint16_t id);
	bool IsExists(uint16_t id);
	bool GetTransmit(uint16_t id, TextDrawTransmit& transmit);
	struct Textdraw* GetTextdraw(uint16_t id);
};

struct Pickup {
	int modelId;
	int	type;
	float position[3];
};

struct WeaponPickup {
	bool exists;
	uint16_t owner;
};

struct SAMPFUNCS_API PickupPool {
	int largestId;
	uint32_t gtaPickupHandle[SAMP_MAX_PICKUPS];
	int id[SAMP_MAX_PICKUPS];
	int time[SAMP_MAX_PICKUPS];
	struct WeaponPickup weaponPickup[SAMP_MAX_PICKUPS];
	struct Pickup pickup[SAMP_MAX_PICKUPS];

	DWORD GetPickupHandleByID(int iID);
	int GetPickupIDByHandle(DWORD dwHandle);
	bool IsPickupExists(int iID);
};

struct RemotePlayerInfo {
	struct RemotePlayer* data;
	int ping;
#ifndef _DEBUG
private:
	int __align;
public:
#endif
	std::string nickname;
	int score;
	BOOL isNpc;
};

struct LocalPlayerInfo {
	int ping;
	int score;
	uint16_t id;
#ifndef _DEBUG
private:
	int __align;
public:
#endif
	std::string nickname;
	struct LocalPlayer* data;	
};

struct SAMPFUNCS_API PlayerPool {
	uint32_t largestPlayerId;		
	RemotePlayerInfo* remotePlayerInfo[SAMP_MAX_PLAYERS];
	int isListed[SAMP_MAX_PLAYERS];
	uint32_t prevCollisionFlag[SAMP_MAX_PLAYERS];
	LocalPlayerInfo localPlayerInfo;

	int SetLocalPlayerName(const char *name);
	int GetSAMPPlayerIDFromGTAHandle(uint32_t GTA_Ped_ID);
	int GetActorHandleFromSAMPPlayerID(int playerId);
	const char* GetPlayerName(int iPlayerID);
	D3DCOLOR GetPlayerColor(int id);
	short GetPlayerAnimation(int iPlayerID);
	bool IsPlayerDefined(int playerId, bool check_streamed = false);
	struct OnFootData* GetOnFootData(int playerId);
	struct InCarData* GetInCarData(int playerId);
	struct PassengerData* GetPassengerData(int playerId);
	struct AimData* GetAimData(int playerId);
	struct TrailerData* GetTrailerData(int playerId);
	bool SetPlayerColor(int id, D3DCOLOR color);
};

struct ControllerState {
	short leftStickX; // move/steer left = -128, right = 128
	short leftStickY; // move back = 128, forwards = -128
	union {
		struct {
			unsigned char leftShoulder1 : 1; // fire weapon alt
			unsigned char shockButtonL : 1; // crouch
			unsigned char buttonCircle : 1; // fire weapon
			unsigned char buttonCross : 1; // sprint, accelerate
			unsigned char buttonTriangle : 1; // enter/exit vehicle
			unsigned char buttonSquare : 1; // jump, reverse
			unsigned char rightShoulder2 : 1; // look right (incar)
			unsigned char rightShoulder1 : 1; // hand brake, target

			unsigned char leftShoulder2 : 1; // look left
			unsigned char shockButtonR : 1; // look behind
			unsigned char pedWalk : 1; // walking
			unsigned char rightStickDown : 1;
			unsigned char rightStickUp : 1;
			unsigned char rightStickRight : 1; // num 4
			unsigned char rightStickLeft : 1; // num 6
		};
		short value;
	};
};

struct Animation {
	union {
		struct {
			unsigned short id : 16;
			unsigned char framedelta : 8;
			unsigned char loopA : 1;
			unsigned char lockX : 1;
			unsigned char lockY : 1;
			unsigned char lockF : 1;
			unsigned char time : 2;
		};
		int value;
	};
};

struct OnFootData {
	ControllerState controllerState;
	float position[3];
	float quaternion[4];
	uint8_t health;
	uint8_t armor;
	uint8_t currentWeapon : 6;
	uint8_t specialKey : 2;
	uint8_t specialAction;
	float moveSpeed[3];
	float surfingOffset[3];
	uint16_t surfingVehicleID;
	Animation currentAnimation;
};

struct InCarData {
	uint16_t vehicleId;
	ControllerState controllerState;
	float quaternion[4];
	float position[3];
	float moveSpeed[3];
	float health;
	uint8_t driverHealth;
	uint8_t driverArmor;
	uint8_t currentWeapon;
	uint8_t sirenState;
	uint8_t landingGearState;
	uint16_t trailerId;
	union {
		uint16_t hydraThrustAngle[2];	//nearly same value
		float trainSpeed;
	};
};

struct AimData {
	uint8_t cameraMode;
	float aimf1[3];
	float aimPos[3];
	float aimZ;
	uint8_t camExtZoom : 6;		// 0-63 normalized
	uint8_t weaponState : 2;	// see eWeaponState
	uint8_t aspectRatio;
};

struct TrailerData {
	uint16_t id;
	float position[3];
	float quaternion[4]; // not tested
	float moveSpeed[3];
	float turnSpeed[3];
};

struct PassengerData {
	uint16_t id;
	uint8_t seatID;
	uint8_t currentWeapon;
	uint8_t health;
	uint8_t armor;
	ControllerState controllerState;
	float position[3];
};

struct UnoccupiedData {
	int16_t id;
	uint8_t seatID;
	float roll[3];
	float direction[3];
	float position[3];
	float moveSpeed[3];
	float turnSpeed[3];
	float health;
};

struct BulletData {
	uint8_t targetType;
	uint16_t targetId;
	float origin[3];
	float target[3];
	float center[3];
	uint8_t weaponId;
};

struct SpectatorData {
	ControllerState controllerState;
	float position[3];
};

struct StatsData {
	int money;
	int drunkLevel;
};

struct HeadSync {
	float direction[3];
	int lastUpdateTick;
	int lastLookTick;
};

struct SAMPFUNCS_API LocalPlayer {
	struct SAMPPed* sampActor;
	struct InCarData inCarData;
	struct AimData aimData;
	struct TrailerData trailerData;
	struct OnFootData onFootData;
	struct PassengerData passengerData;	
	BOOL isActive;
	BOOL isWasted;
	uint16_t currentVehicleID;
	uint16_t lastVehicleID;
	Animation currentAnimation;
	uint32_t animationSynced;
	BOOL isSpectating;
	uint8_t teamId;
	uint16_t unk2;
	uint32_t lastUpdate;
	uint32_t lastSendSpectateTick;
	uint32_t lastSendAimTick;
	uint32_t lastSendStatsTick;
	struct CameraTarget {
		uint16_t objectId;
		uint16_t vehicleId;
		uint16_t playerId;
		uint16_t actorId;
	} cameraTarget;
	uint32_t lastHeadSyncTick;
	struct HeadSync headSyncData;
	uint32_t lastAnyTick;
	BOOL spawnClassIsLoaded;
	uint32_t lastSpawnSelectionTick;
	uint32_t initialSpawnSelectionTick;
	struct SpawnInfo {
		uint8_t teamId;
		int skinId;
		uint8_t unk;
		float position[3];
		float rotation;
		int weapon[3];
		int ammo[3];
	} spawnInfo;
	BOOL hasSpawnInfo;
	uint32_t lastWeaponUpdateTick;
	struct {
		uint16_t aimedPlayerId;
		uint16_t aimedActorId;
		uint8_t currentWeapon;
		uint8_t lastWeapon[13];
		int lastWeaponAmmo[13];
	} weaponsData;
	int passengerDriveByMode;
	uint8_t currentInteriorId;
	BOOL isInRCVehicle;
	char name[256];
	struct SurfData {
		uint16_t entityId;
		uint32_t lastUpdateTick;
		union SAMP_API {
			struct SAMPVehicle* vehicle;
			struct Object* object;
		};
		BOOL stuck;
		BOOL isActive;
		float position[3];
		int unk;	
		SurfingMode mode;
	} surfData;
	struct ClassSelection {
		BOOL enableAfterDeath;
		int selectedSpawnClassId;
		BOOL waitingForRequestToSpawn;
		BOOL isActive;
	} classSelection;
	uint32_t zoneDisplayingEnded;
	struct Spectating {
		SpectatingMode mode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
		SpectatingType type;		// 0 = none, 1 = player, 2 = vehicle
		int objectId;
		BOOL processed;
	} spectating;
	struct DamageData {
		uint16_t lastVehicleId;
		int bumperDamage;
		int doorDamage;
		uint8_t lightDamage;
		uint8_t wheelDamage;
	} vehicleDamageData;

	void Spawn(void);
	void SendDeath(void);
	void SetSpecialAction(uint8_t byteSpecialAction);
	void RequestClass(int ClassId);
	void Say(char* msg);
	void SendEnterVehicle(int vehicleId, int passenger);
	void SendExitVehicle(int vehicleId);
	void ForceSendVehicleSync(uint16_t vehicleId);
	void ForceSendUnoccupiedSync(uint16_t vehicleId, uint8_t seatId);
	void ForceSendOnfootSync(void);
	void ForceSendAimSync(void);
	void ForceSendTrailerSync(uint16_t vehicleId);
	void ForceSendPassengerSync(uint16_t vehicleId, uint8_t seatId);
	void ForceSendStatsSync(void);
	void ForceSendWeaponsSync(void);
};

struct RemotePlayer {
	struct SAMPPed* sampActor;
	struct SAMPVehicle* sampVehicle;
	uint16_t playerId;
	uint16_t vehicleID;
	uint32_t unk;
	BOOL showNametag;
	BOOL hasJetPack;
	uint8_t	specialAction;
	struct InCarData inCarData;
	struct TrailerData trailerData;
	struct AimData aimData;
	struct PassengerData passengerData;
	struct OnFootData onFootData;
	uint8_t teamId;
	PlayerState state;
	uint8_t seatId;
	uint32_t unk2;
	BOOL passengerDriveByMode;
	float onFootPos[3];
	float onFootMoveSpeed[3];
	float vehiclePosition[3];
	float vehicleMoveSpeed[3];
	uint8_t unk3[76];
	float positionDifference[3];
	struct {
		float real;
		float imag[3];
	} vehicleTargetRotation;
	float armor;
	float health;
	char unk4[12];
	Animation currentAnimation;
	UpdateType updateType;
	uint32_t lastUpdateTick;
	uint32_t lastStreamedInTick;	// is 0 when currently streamed in
	BOOL performingCustomAnimation;
	PlayerStatus status;
	struct HeadSync headSyncData;
	struct GlobalMarker {
		int state;
		int position[3];
		uint32_t handle;
	} marker;	
};

struct StreamedOutPlayerInfo {
	float position[SAMP_MAX_PLAYERS][3];
};

template <typename T>
struct SAMPEntity {
	void* vtbl;
	uint8_t byteUnk0[60];
	T* gtaEntity;
	uint32_t gtaEntityHandle;
};

struct Accessory {
	int model;
	int bone;
	float offset[3];
	float rotation[3];
	float scale[3];
	D3DCOLOR firstMaterialColor;
	D3DCOLOR secondMaterialColor;
};

struct SAMPPed : public SAMPEntity<struct actor_info> {
	BOOL usingCellPhone;
	struct Accessories {
		BOOL isListed[SAMP_MAX_ACCESSORIES];
		Accessory accessory[SAMP_MAX_ACCESSORIES];
		struct Object* m_pObject[SAMP_MAX_ACCESSORIES];
	} accessories;
	struct actor_info* gtaPed;
	unsigned int unk[2];
	unsigned char playerNumber;
	unsigned int unk2[2];
	uint16_t parachuteObject;
	uint16_t urinateParticleId;
	struct {
		StuffType type;
		uint32_t m_object;
		int drunkLevel;
	} stuff;
	uint8_t unk3[5];
	struct DanceInfo {
		BOOL isDancing;
		int danceStyle;
		int danceMove;
	} danceInfo;
	uint8_t unk4[20];
	BOOL isUrinating;
	uint8_t unk5[55];
};

struct SAMPFUNCS_API VehiclePool {
	int largestId;
	struct {
		struct Info {
			uint16_t id;
			int type;
			float position[3];
			float rotation;
			uint8_t primaryColor;
			uint8_t	secondaryColor;
			float health;
			char interiorId;
			int doorDamageStatus;
			int panelDamageStatus;
			char lightDamageStatus;
			bool doorsLocked;
			bool hasSiren;
		} entry[100];
		BOOL isAvailable[100];
	} waiting;
	struct SAMPVehicle* sampVehicle[SAMP_MAX_VEHICLES];
	BOOL isListed[SAMP_MAX_VEHICLES];
	struct vehicle_info* gtaVehicle[SAMP_MAX_VEHICLES];
	int	unk[SAMP_MAX_VEHICLES];
	uint16_t lastUndrivenId[SAMP_MAX_VEHICLES];
	int lastUndrivenProcessTick[SAMP_MAX_VEHICLES];
	BOOL isActive[SAMP_MAX_VEHICLES];
	BOOL isDestroyed[SAMP_MAX_VEHICLES];
	int tickWhenDestroyed[SAMP_MAX_VEHICLES];
	float spawnPosition[SAMP_MAX_VEHICLES][3];
	BOOL isInitialized;

	int GetSAMPVehicleIDFromGTAHandle(uint32_t GTA_Vehicle_ID);
	int GetCarHandleFromSAMPCarID(int vehicleId);
};

struct SAMPVehicle : public SAMPEntity<struct vehicle_info> {
	struct vehicle_info* trailer;
	struct vehicle_info* gtaVehicle;
	uint8_t unk[8];
	BOOL isInvulnerable;
	BOOL isLightsOn;
	BOOL isLocked;
	bool isObjective;
	BOOL objectiveBlipCreated;
	int timeSinceLastDriven;
	BOOL m_bHasBeenDriven;
	char unk2[4];
	BOOL engineState;
	unsigned char primaryColor;
	unsigned char secondaryColor;
	BOOL needsToUpdateColor;
	BOOL unoccupiedSync;
	BOOL remoteUnocSync;
	BOOL keepModelLoaded;
	int hasSiren;
	IDirect3DTexture9* licensePlate;
	char licensePlateText[32 + 1];
	uint32_t marker;
};

struct Object : public SAMPEntity<struct object_info> {
	uint8_t unk[6];
	int model;
	uint8_t unk2;
	bool dontCollideWithCamera;
	float drawDistance;
	float unk3;
	float position[3];
	float distanceToCamera;
	bool drawLast;
	uint8_t unk4[64];
	float rotation[3];
};

struct SAMPFUNCS_API ObjectPool {
	int largestId;
	int isListed[SAMP_MAX_OBJECTS];
	struct Object* object[SAMP_MAX_OBJECTS];

	DWORD GetObjectHandleByID(int iID);
	int GetObjectIDByHandle(DWORD dwHandle);
	bool IsObjectExists(int iID);
};

struct Gangzone {
	float position[4];
	uint32_t color;
	uint32_t altColor;
};

struct GangzonePool {
	struct Gangzone* gangzone[SAMP_MAX_GANGZONES];
	BOOL isListed[SAMP_MAX_GANGZONES];
};

struct TextLabel {
	char* text;
	uint32_t color;
	float position[3];
	float maxViewDistance;
	uint8_t showBehindWalls;
	uint16_t attachedToPlayerID;
	uint16_t attachedToVehicleID;
};

struct SAMPFUNCS_API TextLabelPool {
	struct TextLabel textLabel[SAMP_MAX_3DTEXTS];
	int iIsListed[SAMP_MAX_3DTEXTS];

	int Create3DText(uint16_t id, char* szText, D3DCOLOR Color, float fPosition[3], float fViewDistance,
		bool bShowBehindWalls, USHORT sAttachedToPlayer, USHORT sAttachedToVehicle);
	int Create3DText(char* szText, D3DCOLOR Color, float fPosition[3], float fViewDistance,
		bool bShowBehindWalls, USHORT sAttachedToPlayer, USHORT sAttachedToVehicle);
	int Create3DText(uint16_t id, TextLabel textLabel);
	bool Get3DTextInfo(uint16_t id, TextLabel &textLabel);
	bool Destroy3DText(int ID);
};

struct FontRenderer {
	ID3DXFont* chatFont;
	ID3DXFont* littleFont;
	ID3DXFont* chatShadowFont;
	ID3DXFont* littleShadowFont;
	ID3DXFont* carNumberFont;
	ID3DXSprite* tempSprite;
	IDirect3DDevice9* d3dDevice;
	char* textBuffer;
};

struct SAMPFUNCS_API ChatInfo {
	int pagesize;
	void* lastMessage;
	int mode;
	uint8_t timestamps;
	uint32_t logFileIsExist;
	char logFilePath[MAX_PATH + 1];
	void* gameUI; // CDXUTDialog
	void* editBackground; // CDXUTEditBox
	void* dxutScrollBar; // CDXUTScrollBar
	D3DCOLOR textColor;
	D3DCOLOR infoColor;
	D3DCOLOR debugColor;
	uint32_t chatWindowBottom;
	struct ChatEntry {
		uint32_t systemTime;
		char prefix[28];
		char text[144];
		uint8_t unk[64];
		int type;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
		D3DCOLOR textColor;
		D3DCOLOR prefixColor;	// or textOnly colour
	} chatEntry[100];
	FontRenderer* fontRenderer;
	ID3DXSprite* chatTextSprite;
	ID3DXSprite* sprite;
	IDirect3DDevice9* d3dDevice;
	int renderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	ID3DXRenderToSurface* d3dRenderToSurface;
	IDirect3DTexture9* texture;
	IDirect3DSurface9* surface;
	D3DDISPLAYMODE* d3dDisplayMode;
	int unk[2];
	int redraw;
	int scrollBarPosition;
	int fontSizeY;
	int timestampWidth;

	void AddChatMessage(D3DCOLOR Color, const char* Text, ...);
	void AddChatMessage(ChatMessageType Type, const char* szString, const char* szPrefix,
		D3DCOLOR TextColor, D3DCOLOR PrefixColor);
	void SetDisplayMode(int mode);
	void SetChatInputText(char* pstr);
	std::string GetChatInputText();
};

typedef void(__cdecl* CMDPROC) (PCHAR);
struct SAMPFUNCS_API InputInfo {
	void* d3dDevice;
	void* dxutDialog;
	class _CDXUTEditBox* dxutEditBox;
	CMDPROC commandsProcedures[SAMP_MAX_CLIENTCMDS];
	char commandNames[SAMP_MAX_CLIENTCMDS][33];
	int commandsCount;
	BOOL enabled;
	char inputBuffer[129];
	char recallBufffer[10][129];
	char currentBuffer[129];
	int currentRecall;
	int totalRecalls;
	CMDPROC defaultCommand;

	void AddClientCommand(char* Command, DWORD Function);
	void EnableInput(void);
	void DisableInput(void);
	void ProcessInput();
	bool UnregisterClientCommand(char* Command);
};

struct KillInfo {
	BOOL enabled;
	struct KillEntry {
		char killer[25];
		char victim[25];
		D3DCOLOR killerColor;
		D3DCOLOR victimColor;
		uint8_t type;
	} killEntry[5];
	int longestNickLength;
	int position[2];
	ID3DXFont* d3dFont;
	ID3DXFont* weaponFont1;
	ID3DXFont* weaponFont2;
	ID3DXSprite* sprite;
	IDirect3DDevice9* d3dDevice;
	int auxFontInited;
	ID3DXFont* auxFont1;
	ID3DXFont* auxFont2;
};

struct SAMPFUNCS_API DialogInfo {
	void* vtbl;
	int textPosition[2];
	int textSize[2];
	int buttonOffset[2];
	class _CDXUTDialog* dialog;
	class _CDXUTListBox* list;
	class _CDXUTEditBox* editBox;
	int isActive;
	int type;
	uint32_t dialogID;
	char* text;
	uint32_t fontSize[2];
	char caption[65];
	BOOL serverSide;
	char unk[536];

	void Close(int iPressedBtn);
	void ListBoxSetIndex(int iIndex);
	int ListBoxGetIndex(void);
	int ListBoxGetItemsCount(void);
	char* ListBoxGetItemText(int id);
	wchar_t* GetInputText(void);
	void SetInputText(char* pwszText);
	void ShowDialog(uint16_t wDialogId, int iStyle, char* szCaption,
		char* szInfo, char* szButton1, char* szButton2);
	int GetScrollItem();
	void SetScrollItem(int index);
};

struct ChatBubble {
	int exists;
	char text[256];
	uint32_t creationTick;
	uint32_t lifeSpan;
	uint32_t color;
	float drawDistance;
	uint32_t maxLineLength;
};

struct SAMPFUNCS_API MiscInfo {
	struct stAudio {
		int soundState;
	} *audio;
	struct stCamera {
		class CMatrix_Padded* matrix;
	} *camera;
	SAMPPed* localPlayerPed;
	struct RacingCheckpoint {
		float position[3];
		float nextPosition[3];
		float size;
		char type;
		BOOL enabled;
		uint32_t marker;
		uint32_t handle;
	} racingCheckpoint;
	struct Checkpoint {
		float position[3];
		float size[3];
		BOOL enabled;
		uint32_t handle;
	} checkpoint;
	int unk;
	BOOL headIsMove;
	int frameLimiter;
	int	cursorMode;
	unsigned int inputEnableWaitFrames;
	BOOL clockEnabled;
	char unk2;
	bool keepLoadedVehicleModels[212];

	void ToggleCursor(bool bToggle);
	void ToggleCursor(int mode, bool toggle);
	bool IsSettingsValueExists(char *szParam);
	int WriteSettingsValue(char* szParam, int iValue);
	int ReadSettingsValue(char* szParam);
};

struct SAMPFUNCS_API ScoreboardInfo {
	BOOL enabled;
	int playersCount;
	float textOffsets[2];
	float scalar;
	IDirect3DDevice9* directDevice;
	class _CDXUTDialog* d3dDialog;
	class _CDXUTListBox* list;
	int offset;
	BOOL isSorted;

	void Enable(bool enable);
};

struct ActorPool {
	int largestId;
	SAMPEntity<void>* actor[SAMP_MAX_ACTORS]; // ?
	int isListed[SAMP_MAX_ACTORS];
	struct actor_info* gtaPed[SAMP_MAX_ACTORS];
	uint32_t unk[SAMP_MAX_ACTORS];
	uint32_t unk1[SAMP_MAX_ACTORS];
};

struct ChatBubbleInfo {
	struct ChatBubble chatBubble[SAMP_MAX_PLAYERS];
};

#pragma pack(pop)

class SAMPFUNCS_API SFSAMP {
	SFPluginInfo* m_PluginInfo;
public:
	typedef void(__stdcall* dialogCallback_t)(int dialogId, int buttonId, int listItem, const char* input);

	SFSAMP(SFPluginInfo* pluginInfo);
	SFPluginInfo* getPluginInfo(void);

	bool IsInitialized(void);
	DWORD getSAMPAddr(void);

	struct NetGame* getNetGame(void);
	struct PlayerPool* getPlayers(void);
	struct VehiclePool* getVehicles(void);
	struct ChatInfo* getChat(void);
	struct InputInfo* getInput(void);
	struct KillInfo* getDeathList(void);
	struct DialogInfo* getDialog(void);
	struct MiscInfo* getMisc(void);
	struct ScoreboardInfo* getScoreboard(void);
	struct StreamedOutPlayerInfo* getStreamedOutInfo(void);

	bool registerChatCommand(std::string command, CommandProc callback);
	bool registerDialogCallback(dialogCallback_t callback);
	void disconnect(int Reason);
	void requestClass(int ClassId);
	void sendSCMEvent(int vehicleId, int iEvent, int iParam1, int iParam2);
	void sendEnterVehicle(int vehicleId, int passenger);
	void sendExitVehicle(int vehicleId);
	void sendSpawn(void);
	void sendWastedNotification(uint8_t reason, uint16_t playerId);
	void sendRCONCommand(char* pszCommand);
	void sendDamageVehicle(WORD vehicleID, DWORD panel, DWORD door, BYTE lights, BYTE tires);
	void sendClickPlayer(uint16_t playerId, uint8_t source);
	void sendDialogResponse(uint16_t dialogId, uint8_t button, uint16_t listItem, char *pszInput);
	void sendClickTextDraw(uint16_t textDrawId);
	void sendGiveDamage(uint16_t targetId, float damage, int weapon, int bodypart);
	void sendTakeDamage(uint16_t issuerId, float damage, int weapon, int bodypart);
	void sendEditObject(bool playerObject, uint16_t objectId, int response,
		float pos_x, float pos_y, float pos_z,
		float rot_x, float rot_y, float rot_z);
	void sendEditAttachedObject(int response, int id, int model, int bone,
		float offset_x, float offset_y, float offset_z,
		float rot_x, float rot_y, float rot_z,
		float scale_x, float scale_y, float scale_z);
	void sendInteriorChange(uint8_t interiorId);
	void sendRequestSpawn(void);
	void sendPickedUpPickup(int pickup);
	void sendMenuSelect(uint8_t row);
	void sendMenuQuit(void);
	void sendVehicleDestroyed(uint16_t vehicleId);
	void setSendRate(SendrateType eType, int iValue);
	void takeScreenShot(void);
	void setChatCommandDescription(std::string command, std::string description);
};

#endif // SFSAMP_H__
