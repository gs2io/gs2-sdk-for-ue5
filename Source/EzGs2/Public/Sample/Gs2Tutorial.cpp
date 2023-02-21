// Fill out your copyright notice in the Description page of Project Settings.


#include "Sample/Gs2Tutorial.h"

#include "Core/Gs2Domain.h"
#include "Util/Gs2AccountAuthenticator.h"
#include "Util/Gs2BasicReOpener.h"
#include "Util/Profile.h"

DEFINE_LOG_CATEGORY(GameLog);


class EZGS2_API FSampleTask final : public Gs2::Core::Util::TGs2Future<void*>
{
public:
	virtual ~FSampleTask() override = default;

	virtual Gs2::Core::Model::FGs2ErrorPtr Action(const TSharedPtr<TSharedPtr<void*>> Result) override
	{
		// Setup variables

		const auto ClientId = "YourClientId";
		const auto ClientSecret = "YourClientSecret";
		const auto AccountNamespaceName = "game-0001";
		const auto AccountEncryptionKeyId = "grn:gs2:{region}:{ownerId}:key:account-encryption-key-namespace:key:account-encryption-key";
		
		// Setup general setting
		
		const auto Profile = MakeShared<Gs2::UE5::Util::FProfile>(
			ClientId,
			ClientSecret,
			Gs2::Core::Model::ERegion::ApNorthEast1,
			MakeShareable<Gs2::UE5::Util::IReOpener>(new Gs2::UE5::Util::FGs2BasicReOpener())
		);

		// Create GS2 client
		const auto InitializeFuture = Profile->Initialize();
		InitializeFuture->StartSynchronousTask();
		if (InitializeFuture->GetTask().IsError())
		{
			UE_LOG(GameLog, Error, TEXT("%s"), ToCStr(InitializeFuture->GetTask().Error()->String()));
			return InitializeFuture->GetTask().Error();
		}
		const auto Gs2 = InitializeFuture->GetTask().Result();

		// Create an anonymous account
		
		UE_LOG(GameLog, Display, TEXT("Create anonymous account"));

		const auto CreateFuture = Gs2->Account->Namespace(
			AccountNamespaceName
		)->Create();
		CreateFuture->StartSynchronousTask();
		if (CreateFuture->GetTask().IsError())
		{
			UE_LOG(GameLog, Error, TEXT("%s"), ToCStr(CreateFuture->GetTask().Error()->String()));
			return CreateFuture->GetTask().Error();
		}

		// Load created account

		const auto LoadFuture = CreateFuture->GetTask().Result()->Model();
		LoadFuture->StartSynchronousTask();
		if (LoadFuture->GetTask().IsError())
		{
			UE_LOG(GameLog, Error, TEXT("%s"), ToCStr(LoadFuture->GetTask().Error()->String()));
			return LoadFuture->GetTask().Error();
		}
		const auto Account = LoadFuture->GetTask().Result();

		// Dump anonymous account

		UE_LOG(GameLog, Display, TEXT("UserId: %s"), ToCStr(*Account->GetUserId()));
		UE_LOG(GameLog, Display, TEXT("Password: %s"), ToCStr(*Account->GetPassword()));

		// Log-in created anonymous account

		const auto LoginFuture = Profile->Login(
			MakeShareable<Gs2::UE5::Util::IAuthenticator>(
				new Gs2::UE5::Util::FGs2AccountAuthenticator(
					AccountNamespaceName,
					AccountEncryptionKeyId
				)
			),
			*Account->GetUserId(),
			*Account->GetPassword()
		);
		LoginFuture->StartSynchronousTask();
		if (LoginFuture->GetTask().IsError())
		{
			UE_LOG(GameLog, Error, TEXT("%s"), ToCStr(LoginFuture->GetTask().Error()->String()));
			return LoginFuture->GetTask().Error();
		}
		const auto GameSession = LoginFuture->GetTask().Result();

		// Load TakeOver settings

		const auto It = Gs2->Account->Namespace(
			AccountNamespaceName
		)->Me(
			GameSession
		)->TakeOvers();
		for (auto TakeOver : *It)
		{
			UE_LOG(GameLog, Display, TEXT("Type: %d"), *TakeOver->GetType());
			UE_LOG(GameLog, Display, TEXT("Identifier: %s"), ToCStr(*TakeOver->GetUserIdentifier()));
		}

		// Finalize GS2-SDK
		
		const auto FinalizeFuture = Profile->Finalize();
		FinalizeFuture->StartSynchronousTask();
		if (FinalizeFuture->GetTask().IsError())
		{
			UE_LOG(GameLog, Error, TEXT("%s"), ToCStr(FinalizeFuture->GetTask().Error()->String()));
			return FinalizeFuture->GetTask().Error();
		}

		return nullptr;
	}
};

AGs2Tutorial::AGs2Tutorial()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGs2Tutorial::BeginPlay()
{
	Super::BeginPlay();

	(new FAsyncTask<FSampleTask>())->StartBackgroundTask();
}

void AGs2Tutorial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

