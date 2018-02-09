// Property of D4L4L

#include "TankProjectile.h"


// Sets default values
ATankProjectile::ATankProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisonMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisonMesh);
	CollisonMesh->SetNotifyRigidBodyCollision(true);
	CollisonMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ImpactForce = CreateDefaultSubobject<URadialForceComponent>(FName("Impact Force"));
	ImpactForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();

	/// Delegates the event to the specified method 
	/// if the collisonMesh hits something this method is called
	CollisonMesh->OnComponentHit.AddDynamic(this, &ATankProjectile::OnHit);
	
}

// Called every frame
void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}


void ATankProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ImpactForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisonMesh->DestroyComponent();
	
	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ImpactForce->Radius, // same radius
		UDamageType::StaticClass(),
		TArray<AActor*>() // damage all
	);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(
		Timer,
		this,
		&ATankProjectile::OnTimerExpire,
		DestroyDelay,
		false
	);
}


void ATankProjectile::OnTimerExpire()
{
	Destroy();
}