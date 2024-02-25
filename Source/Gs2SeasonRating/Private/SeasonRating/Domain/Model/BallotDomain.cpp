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

#include "SeasonRating/Domain/Model/Ballot.h"
#include "SeasonRating/Domain/Model/Namespace.h"
#include "SeasonRating/Domain/Model/MatchSession.h"
#include "SeasonRating/Domain/Model/SeasonModelMaster.h"
#include "SeasonRating/Domain/Model/SeasonModel.h"
#include "SeasonRating/Domain/Model/CurrentSeasonModelMaster.h"
#include "SeasonRating/Domain/Model/Ballot.h"
#include "SeasonRating/Domain/Model/BallotAccessToken.h"
#include "SeasonRating/Domain/Model/Vote.h"
#include "SeasonRating/Domain/Model/User.h"
#include "SeasonRating/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::SeasonRating::Domain::Model
{

    FBallotDomain::FBallotDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SeasonRating::FGs2SeasonRatingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::SeasonRating::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Ballot"
        ))
    {
    }

    FBallotDomain::FBallotDomain(
        const FBallotDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FBallotDomain::FGetTask::FGetTask(
        const TSharedPtr<FBallotDomain>& Self,
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
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FBallot>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
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
                const auto ParentKey = Gs2::SeasonRating::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Ballot"
                );
                const auto Key = Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::SeasonRating::Model::FBallot::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
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
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FBallotDomain::CreateCacheKey(
    )
    {
        return "Singleton";
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
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FBallot>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::SeasonRating::Model::FBallot> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::SeasonRating::Model::FBallot>(
            Self->ParentKey,
            Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SeasonRating::Request::FGetBallotByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::SeasonRating::Model::FBallot::TypeName,
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
            Self->Gs2->Cache->TryGet<Gs2::SeasonRating::Model::FBallot>(
                Self->ParentKey,
                Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(
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

    Gs2::Core::Domain::CallbackID FBallotDomain::Subscribe(
        TFunction<void(Gs2::SeasonRating::Model::FBallotPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::SeasonRating::Model::FBallot::TypeName,
            ParentKey,
            Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SeasonRating::Model::FBallot>(obj));
            }
        );
    }

    void FBallotDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::SeasonRating::Model::FBallot::TypeName,
            ParentKey,
            Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(
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

