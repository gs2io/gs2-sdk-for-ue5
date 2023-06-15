/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
*
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Matchmaking/Domain/Model/Ballot.h"
#include "Matchmaking/Domain/Model/Namespace.h"
#include "Matchmaking/Domain/Model/Gathering.h"
#include "Matchmaking/Domain/Model/GatheringAccessToken.h"
#include "Matchmaking/Domain/Model/RatingModelMaster.h"
#include "Matchmaking/Domain/Model/RatingModel.h"
#include "Matchmaking/Domain/Model/CurrentRatingModelMaster.h"
#include "Matchmaking/Domain/Model/Rating.h"
#include "Matchmaking/Domain/Model/RatingAccessToken.h"
#include "Matchmaking/Domain/Model/Ballot.h"
#include "Matchmaking/Domain/Model/BallotAccessToken.h"
#include "Matchmaking/Domain/Model/Vote.h"
#include "Matchmaking/Domain/Model/User.h"
#include "Matchmaking/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FBallotDomain::FBallotDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> RatingName,
        const TOptional<FString> GatheringName,
        const TOptional<int32> NumberOfPlayer,
        const TOptional<FString> KeyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        RatingName(RatingName),
        GatheringName(GatheringName),
        NumberOfPlayer(NumberOfPlayer),
        KeyId(KeyId),
        ParentKey(Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Ballot"
        ))
    {
    }

    FBallotDomain::FBallotDomain(
        const FBallotDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FBallotDomain::FGetTask::FGetTask(
        const TSharedPtr<FBallotDomain> Self,
        const Request::FGetBallotByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBallotDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBallotDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRatingName(Self->RatingName)
            ->WithGatheringName(Self->GatheringName)
            ->WithNumberOfPlayer(Self->NumberOfPlayer)
            ->WithKeyId(Self->KeyId);
        const auto Future = Self->Client->GetBallotByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Ballot"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRatingName(),
                    ResultModel->GetItem()->GetGatheringName(),
                    ResultModel->GetItem()->GetNumberOfPlayer().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetNumberOfPlayer()) : TOptional<FString>(),
                    RequestModel->GetKeyId()
                );
                Self->Cache->Put(
                    Gs2::Matchmaking::Model::FBallot::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        Domain->Body = *ResultModel->GetBody();
        Domain->Signature = *ResultModel->GetSignature();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBallotDomain::FGetTask>> FBallotDomain::Get(
        Request::FGetBallotByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FBallotDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RatingName,
        TOptional<FString> GatheringName,
        TOptional<FString> NumberOfPlayer,
        TOptional<FString> KeyId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RatingName.IsSet() ? *RatingName : "null") + ":" +
            (GatheringName.IsSet() ? *GatheringName : "null") + ":" +
            (NumberOfPlayer.IsSet() ? *NumberOfPlayer : "null") + ":" +
            (KeyId.IsSet() ? *KeyId : "null") + ":" +
            ChildType;
    }

    FString FBallotDomain::CreateCacheKey(
        TOptional<FString> RatingName,
        TOptional<FString> GatheringName,
        TOptional<FString> NumberOfPlayer,
        TOptional<FString> KeyId
    )
    {
        return FString() +
            (RatingName.IsSet() ? *RatingName : "null") + ":" + 
            (GatheringName.IsSet() ? *GatheringName : "null") + ":" + 
            (NumberOfPlayer.IsSet() ? *NumberOfPlayer : "null") + ":" + 
            (KeyId.IsSet() ? *KeyId : "null");
    }

    FBallotDomain::FModelTask::FModelTask(
        const TSharedPtr<FBallotDomain> Self
    ): Self(Self)
    {

    }

    FBallotDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBallotDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FBallot>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Matchmaking::Model::FBallot> Value = nullptr;
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Matchmaking::Request::FGetBallotByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                Self->Cache->Put(
                    Gs2::Matchmaking::Model::FBallot::TypeName,
                    Self->ParentKey,
                    Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                        Self->RatingName,
                        Self->GatheringName,
                        Self->NumberOfPlayer.IsSet() ? FString::FromInt(*Self->NumberOfPlayer) : TOptional<FString>(),
                        Self->KeyId
                    ),
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "ballot")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Matchmaking::Model::FBallot>(
                Self->ParentKey,
                Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                    Self->RatingName,
                    Self->GatheringName,
                    Self->NumberOfPlayer.IsSet() ? FString::FromInt(*Self->NumberOfPlayer) : TOptional<FString>(),
                    Self->KeyId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBallotDomain::FModelTask>> FBallotDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBallotDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

