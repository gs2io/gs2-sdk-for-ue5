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
#include "SeasonRating/Model/Cache/MatchSession.h"

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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
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
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::SeasonRating::Model::Cache::FMatchSessionCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetSessionName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSessionName(Self->SessionName);
        const auto Future = Self->Client->DeleteMatchSession(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


              Gs2::SeasonRating::Model::Cache::FMatchSessionCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetSessionName(),
            TOptional<int32>()
        );
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
        const auto CacheParentKey = Gs2::SeasonRating::Model::Cache::FMatchSessionCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::SeasonRating::Model::Cache::FMatchSessionCache::CreateCacheKey(

            Self->SessionName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::SeasonRating::Model::FMatchSession::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::SeasonRating::Model::FMatchSessionPtr Value;
                const auto CacheHit = Gs2::SeasonRating::Model::Cache::FMatchSessionCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->SessionName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::SeasonRating::Model::Cache::FMatchSessionCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->SessionName,
                    TOptional<int32>(),
                    [Self](Gs2::SeasonRating::Model::FMatchSessionPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::SeasonRating::Request::FGetMatchSessionRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FMatchSessionDomain::FModelTask>> FMatchSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMatchSessionDomain::FModelTask>>(this->AsShared());
    }

    void FMatchSessionDomain::Invalidate()
    {
        Gs2::SeasonRating::Model::Cache::FMatchSessionCache::Delete(
            Gs2->Cache,

            NamespaceName,
            SessionName,
            TOptional<int32>()
        );
    }

    FMatchSessionDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FMatchSessionDomain>& Self,
        TFunction<void(Gs2::SeasonRating::Model::FMatchSessionPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FMatchSessionDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMatchSessionDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMatchSessionDomain::FSubscribeWithInitialCallTask>> FMatchSessionDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::SeasonRating::Model::FMatchSessionPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FMatchSessionDomain::Subscribe(
        TFunction<void(Gs2::SeasonRating::Model::FMatchSessionPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::SeasonRating::Model::Cache::FMatchSessionCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SeasonRating::Model::Cache::FMatchSessionCache::CreateCacheKey(

            SessionName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<SeasonRating::Domain::FGs2SeasonRatingDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QuerySessionName = SessionName;
        return Gs2->Cache->Subscribe(
            Gs2::SeasonRating::Model::FMatchSession::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SeasonRating::Model::FMatchSession>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QuerySessionName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FMatchSessionDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QuerySessionName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FMatchSessionDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::SeasonRating::Model::Cache::FMatchSessionCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SeasonRating::Model::Cache::FMatchSessionCache::CreateCacheKey(

            SessionName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::SeasonRating::Model::FMatchSession::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
