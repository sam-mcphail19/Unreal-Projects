#include "MinecraftPlayer.h"

AMinecraftPlayer::AMinecraftPlayer() {
	PrimaryActorTick.bCanEverTick = true;

	/*Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//RootComponent = Mesh;
	//SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);
	*/
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0, 0, 50));
}

// Called when the game starts or when spawned
void AMinecraftPlayer::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AMinecraftPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMinecraftPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	InputComponent->BindAxis("LookUp", this, &AMinecraftPlayer::LookUp);
	InputComponent->BindAxis("LookRight", this, &AMinecraftPlayer::LookRight);
	InputComponent->BindAxis("MoveForward", this, &AMinecraftPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMinecraftPlayer::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMinecraftPlayer::Jump);
}

void AMinecraftPlayer::LookUp(float Value) {
	if (Value)
		AddControllerPitchInput(-Value);
}

void AMinecraftPlayer::LookRight(float Value) {
	if (Value)
		AddControllerYawInput(Value);
}

void AMinecraftPlayer::MoveForward(float Value) {
	if (Value)
		AddMovementInput(Camera->GetForwardVector(), Value);
}

void AMinecraftPlayer::MoveRight(float Value) {
	if (Value)
		AddMovementInput(Camera->GetRightVector(), Value);
}