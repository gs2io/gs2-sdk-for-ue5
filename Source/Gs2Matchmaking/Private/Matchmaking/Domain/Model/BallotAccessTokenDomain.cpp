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
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Matchmaking/Domain/Model/BallotAccessToken.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FBallotAccessTokenDomain::FBallotAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> RatingName,
        const TOptional<FString> GatheringName,
        const TOptional<int32> NumberOfPlayer,
        const TOptional<FString> KeyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RatingName(RatingName),
        GatheringName(GatheringName),
        NumberOfPlayer(NumberOfPlayer),
        KeyId(KeyId),
        ParentKey(Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Ballot"
        ))
    {
    }

    FBallotAccessTokenDomain::FBallotAccessTokenDomain(
        const FBallotAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RatingName(From.RatingName),
        GatheringName(From.GatheringName),
        NumberOfPlayer(From.NumberOfPlayer),
        KeyId(From.KeyId),
        ParentKey(From.ParentKey)
    {

    }

    FBallotAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FBallotAccessTokenDomain>& Self,
        const Request::FGetBallotRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBallotAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBallotAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRatingName(Self->RatingName)
            ->WithGatheringName(Self->GatheringName)
            ->WithNumberOfPlayer(Self->NumberOfPlayer)
            ->WithKeyId(Self->KeyId);
        const auto Future = Self->Client->GetBallot(
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
                    Self->UserId(),
                    "Ballot"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRatingName(),
                    ResultModel->GetItem()->GetGatheringName(),
                    ResultModel->GetItem()->GetNumberOfPlayer().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetNumberOfPlayer()) : TOptional<FString>(),
                    RequestModel->GetKeyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FBallot::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->Body = *ResultModel->GetBody();
            Domain->Signature = *ResultModel->GetSignature();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBallotAccessTokenDomain::FGetTask>> FBallotAccessTokenDomain::Get(
        Request::FGetBallotRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FBallotAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RatingName,
        TOptional<FString> GatheringName,
        TOptional<FString> NumberOfPlayer,
        TOptional<FString> KeyId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RatingName.IsSet() ? *RatingName : "null") + ":" +
            (GatheringName.IsSet() ? *GatheringName : "null") + ":" +
            (NumberOfPlayer.IsSet() ? *NumberOfPlayer : "null") + ":" +
            (KeyId.IsSet() ? *KeyId : "null") + ":" +
            ChildType;
    }

    FString FBallotAccessTokenDomain::CreateCacheKey(
        TOptional<FString> RatingName,
        TOptional<FString> GatheringName,
        TOptional<FString> NumberOfPlayer,
        TOptional<FString> KeyId
    )
    {
        return FString("") +
            (RatingName.IsSet() ? *RatingName : "null") + ":" + 
            (GatheringName.IsSet() ? *GatheringName : "null") + ":" + 
            (NumberOfPlayer.IsSet() ? *NumberOfPlayer : "null") + ":" + 
            (KeyId.IsSet() ? *KeyId : "null");
    }

    FBallotAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FBallotAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FBallotAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBallotAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FBallot>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Matchmaking::Model::FBallot> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FBallot>(
            Self->ParentKey,
            Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                Self->RatingName,
                Self->GatheringName,
                Self->NumberOfPlayer.IsSet() ? FString::FromInt(*Self->NumberOfPlayer) : TOptional<FString>(),
                Self->KeyId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Matchmaking::Request::FGetBallotRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                    Self->RatingName,
                    Self->GatheringName,
                    Self->NumberOfPlayer.IsSet() ? FString::FromInt(*Self->NumberOfPlayer) : TOptional<FString>(),
                    Self->KeyId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FBallot::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "ballot")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FBallot>(
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

    TSharedPtr<FAsyncTask<FBallotAccessTokenDomain::FModelTask>> FBallotAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBallotAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FBallotAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FBallotPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Matchmaking::Model::FBallot::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                RatingName,
                GatheringName,
                NumberOfPlayer.IsSet() ? FString::FromInt(*NumberOfPlayer) : TOptional<FString>(),
                KeyId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FBallot>(obj));
            }
        );
    }

    void FBallotAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FBallot::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                RatingName,
                GatheringName,
                NumberOfPlayer.IsSet() ? FString::FromInt(*NumberOfPlayer) : TOptional<FString>(),
                KeyId
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

