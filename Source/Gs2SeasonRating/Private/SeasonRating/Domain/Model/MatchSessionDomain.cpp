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

#include "SeasonRating/Domain/Model/MatchSession.h"
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

    FMatchSessionDomain::FMatchSessionDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> SessionName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SeasonRating::FGs2SeasonRatingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        SessionName(SessionName),
        ParentKey(Gs2::SeasonRating::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "MatchSession"
        ))
    {
    }

    FMatchSessionDomain::FMatchSessionDomain(
        const FMatchSessionDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        SessionName(From.SessionName),
        ParentKey(From.ParentKey)
    {

    }

    FMatchSessionDomain::FGetTask::FGetTask(
        const TSharedPtr<FMatchSessionDomain>& Self,
        const Request::FGetMatchSessionRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMatchSessionDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMatchSessionDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FMatchSession>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSessionName(Self->SessionName);
        const auto Future = Self->Client->GetMatchSession(
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
                const auto ParentKey = Gs2::SeasonRating::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MatchSession"
                );
                const auto Key = Gs2::SeasonRating::Domain::Model::FMatchSessionDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SeasonRating::Model::FMatchSession::TypeName,
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

    TSharedPtr<FAsyncTask<FMatchSessionDomain::FGetTask>> FMatchSessionDomain::Get(
        Request::FGetMatchSessionRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMatchSessionDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMatchSessionDomain>& Self,
        const Request::FDeleteMatchSessionRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMatchSessionDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMatchSessionDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FMatchSessionDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSessionName(Self->SessionName);
        const auto Future = Self->Client->DeleteMatchSession(
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
                const auto ParentKey = Gs2::SeasonRating::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MatchSession"
                );
                const auto Key = Gs2::SeasonRating::Domain::Model::FMatchSessionDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::SeasonRating::Model::FMatchSession::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMatchSessionDomain::FDeleteTask>> FMatchSessionDomain::Delete(
        Request::FDeleteMatchSessionRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FMatchSessionDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> SessionName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (SessionName.IsSet() ? *SessionName : "null") + ":" +
            ChildType;
    }

    FString FMatchSessionDomain::CreateCacheKey(
        TOptional<FString> SessionName
    )
    {
        return FString("") +
            (SessionName.IsSet() ? *SessionName : "null");
    }

    FMatchSessionDomain::FModelTask::FModelTask(
        const TSharedPtr<FMatchSessionDomain> Self
    ): Self(Self)
    {

    }

    FMatchSessionDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMatchSessionDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FMatchSession>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::SeasonRating::Model::FMatchSession> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::SeasonRating::Model::FMatchSession>(
            Self->ParentKey,
            Gs2::SeasonRating::Domain::Model::FMatchSessionDomain::CreateCacheKey(
                Self->SessionName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SeasonRating::Request::FGetMatchSessionRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::SeasonRating::Domain::Model::FMatchSessionDomain::CreateCacheKey(
                    Self->SessionName
                );
                Self->Gs2->Cache->Put(
                    Gs2::SeasonRating::Model::FMatchSession::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "matchSession")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::SeasonRating::Model::FMatchSession>(
                Self->ParentKey,
                Gs2::SeasonRating::Domain::Model::FMatchSessionDomain::CreateCacheKey(
                    Self->SessionName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMatchSessionDomain::FModelTask>> FMatchSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMatchSessionDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FMatchSessionDomain::Subscribe(
        TFunction<void(Gs2::SeasonRating::Model::FMatchSessionPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::SeasonRating::Model::FMatchSession::TypeName,
            ParentKey,
            Gs2::SeasonRating::Domain::Model::FMatchSessionDomain::CreateCacheKey(
                SessionName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SeasonRating::Model::FMatchSession>(obj));
            }
        );
    }

    void FMatchSessionDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::SeasonRating::Model::FMatchSession::TypeName,
            ParentKey,
            Gs2::SeasonRating::Domain::Model::FMatchSessionDomain::CreateCacheKey(
                SessionName
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

