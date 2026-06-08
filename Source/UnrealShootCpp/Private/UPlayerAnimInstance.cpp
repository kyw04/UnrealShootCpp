#include "UPlayerAnimInstance.h"
#include "ACPlayer.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* owner = TryGetPawnOwner();
	if (!owner)
		return;

	ACPlayer* player = Cast<ACPlayer>(owner);
	if (!player)
		return;

	isAttack = player->isAttack;
	isHit = player->isHit;
	isDie = player->isDie;
	attackSpeed = player->bulletDelay;
}

void UPlayerAnimInstance::SpawnBullet()
{
	APawn* owner = TryGetPawnOwner();
	if (!owner)
		return;
	ACPlayer* player = Cast<ACPlayer>(owner);
	if (!player)
		return;
	
	player->Super::BulletSpawn();
}

void UPlayerAnimInstance::SetPlayerIsAttack(bool value)
{
	APawn* owner = TryGetPawnOwner();
	if (!owner)
		return;
	ACPlayer* player = Cast<ACPlayer>(owner);
	if (!player)
		return;
	
	player->isAttack = value;
}

void UPlayerAnimInstance::SetPlayerIsHit(bool value)
{
	APawn* owner = TryGetPawnOwner();
	if (!owner)
		return;
	ACPlayer* player = Cast<ACPlayer>(owner);
	if (!player)
		return;
	
	player->isHit = value;
}

void UPlayerAnimInstance::SetPlayerIsDie(bool value)
{
	APawn* owner = TryGetPawnOwner();
	if (!owner)
		return;
	ACPlayer* player = Cast<ACPlayer>(owner);
	if (!player)
		return;
	
	player->isDie = value;
}
