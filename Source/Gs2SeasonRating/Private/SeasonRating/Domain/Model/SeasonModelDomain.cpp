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

#include "SeasonRating/Domain/Model/SeasonModel.h"
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
#include "SeasonRating/Model/Cache/SeasonModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::SeasonRating::Domain::Model
{

    FSeasonModelDomain::FSeasonModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> SeasonName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SeasonRating::FGs2SeasonRatingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        SeasonName(SeasonName),
        ParentKey(Gs2::SeasonRating::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "SeasonModel"
        ))
    {
    }

    FSeasonModelDomain::FSeasonModelDomain(
        const FSeasonModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        SeasonName(From.SeasonName),
        ParentKey(From.ParentKey)
    {

    }

    FSeasonModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FSeasonModelDomain>& Self,
        const Request::FGetSeasonModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FSeasonModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName);
        const auto Future = Self->Client->GetSeasonModel(
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


        Gs2::SeasonRating::Model::Cache::FSeasonModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetSeasonName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonModelDomain::FGetTask>> FSeasonModelDomain::Get(
        Request::FGetSeasonModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FSeasonModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> SeasonName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" +
            ChildType;
    }

    FString FSeasonModelDomain::CreateCacheKey(
        TOptional<FString> SeasonName
    )
    {
        return FString("") +
            (SeasonName.IsSet() ? *SeasonName : "null");
    }

    FSeasonModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FSeasonModelDomain> Self
    ): Self(Self)
    {

    }

    FSeasonModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FSeasonModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::SeasonRating::Model::Cache::FSeasonModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::SeasonRating::Model::Cache::FSeasonModelCache::CreateCacheKey(

            Self->SeasonName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::SeasonRating::Model::FSeasonModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::SeasonRating::Model::FSeasonModelPtr Value;
                const auto CacheHit = Gs2::SeasonRating::Model::Cache::FSeasonModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->SeasonName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::SeasonRating::Model::Cache::FSeasonModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->SeasonName,
                    TOptional<int32>(),
                    [Self](Gs2::SeasonRating::Model::FSeasonModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::SeasonRating::Request::FGetSeasonModelRequest>()
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

    TSharedPtr<FAsyncTask<FSeasonModelDomain::FModelTask>> FSeasonModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSeasonModelDomain::FModelTask>>(this->AsShared());
    }

    void FSeasonModelDomain::Invalidate()
    {
        Gs2::SeasonRating::Model::Cache::FSeasonModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            SeasonName,
            TOptional<int32>()
        );
    }

    FSeasonModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FSeasonModelDomain>& Self,
        TFunction<void(Gs2::SeasonRating::Model::FSeasonModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FSeasonModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FSeasonModelDomain::FSubscribeWithInitialCallTask>> FSeasonModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::SeasonRating::Model::FSeasonModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FSeasonModelDomain::Subscribe(
        TFunction<void(Gs2::SeasonRating::Model::FSeasonModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::SeasonRating::Model::Cache::FSeasonModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SeasonRating::Model::Cache::FSeasonModelCache::CreateCacheKey(

            SeasonName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<SeasonRating::Domain::FGs2SeasonRatingDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QuerySeasonName = SeasonName;
        return Gs2->Cache->Subscribe(
            Gs2::SeasonRating::Model::FSeasonModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SeasonRating::Model::FSeasonModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QuerySeasonName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FSeasonModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QuerySeasonName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSeasonModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::SeasonRating::Model::Cache::FSeasonModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SeasonRating::Model::Cache::FSeasonModelCache::CreateCacheKey(

            SeasonName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::SeasonRating::Model::FSeasonModel::TypeName,
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
