#include "ABullet.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"

ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;
    currentTime = 0.0f;

    boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    RootComponent = boxComp;
    boxComp->SetCollisionProfileName(TEXT("OverlapAll"));
    boxComp->SetBoxExtent(FVector(10.0f));

    bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
    bodyMeshComp->SetupAttachment(boxComp);
    bodyMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
    bodyMeshComp->SetRelativeRotation(FRotator(180.0f, 0.0f, 0.0f));
    bodyMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/egg.egg'"));
    if (tempMesh.Succeeded())
    {
        bodyMeshComp->SetStaticMesh(tempMesh.Object);
        bodyMeshComp->SetRelativeScale3D(FVector(0.1f));
    }
}

void ABullet::BeginPlay()
{
    Super::BeginPlay();
    
    realtimePositions = SetPosition(RotatePosition(positions, angle));
}

void ABullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (const auto& pos : realtimePositions)
    {
        DrawDebugCircle(GetWorld(), pos, 10.0f, 16, FColor::Yellow, false, -1.0f);
    }

    currentTime += DeltaTime * speed;
    if (currentTime >= 1.0f)
    {
        if (loop)
        {
            realtimePositions = SetPosition(RotatePosition(positions, angle));
            currentTime -= 1.0f;
        }
        else
        {
            Destroy();
            return;
        }
    }

    FVector newPos = GetBezierCurvePosition();
    SetActorLocation(newPos);

    DrawDebugCircle(GetWorld(), newPos, 15.0f, 16, FColor::Red, false, -1.0f);
}

FVector ABullet::GetBezierCurvePosition()
{
    FVector temp = FVector::ZeroVector;
    int32 n = realtimePositions.Num() - 1;

    if (n < 0) return GetActorLocation();

    for (int32 i = 0; i <= n; i++)
    {
        int32 coeff = Combination(n, i);
        double term = coeff * FMath::Pow(currentTime, i) * FMath::Pow(1.0f - currentTime, n - i);
        temp += realtimePositions[i] * term;
    }

    return temp;
}

int32 ABullet::Combination(int32 n, int32 r)
{
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;

    if (r > n / 2) r = n - r;

    int32 ans = 1;
    for (int32 j = 1; j <= r; j++)
    {
        ans *= (n - j + 1);
        ans /= j;
    }
    return ans;
}

TArray<FVector> ABullet::SetPosition(TArray<FVector> pos)
{
    TArray<FVector> result;
    FVector actorLocation = GetActorLocation();
    for (const auto& p : pos)
    {
        result.Add(actorLocation + p);
    }
    return result;
}

TArray<FVector> ABullet::RotatePosition(TArray<FVector> pos, float degrees)
{
    TArray<FVector> result;
    const float rad = FMath::DegreesToRadians(degrees);
    const float c = FMath::Cos(rad);
    const float s = FMath::Sin(rad);
    for (const auto& p : pos)
    {
        const double y = p.Y * c - p.Z * s;
        const double z = p.Y * s + p.Z * c;
        result.Add(FVector(p.X, y, z));
    }
    return result;
}