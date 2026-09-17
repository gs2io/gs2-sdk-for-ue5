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

#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Domain/Model/Namespace.h"
#include "Experience/Domain/Model/ExperienceModelMaster.h"
#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Domain/Model/ThresholdMaster.h"
#include "Experience/Domain/Model/CurrentExperienceMaster.h"
#include "Experience/Domain/Model/User.h"
#include "Experience/Domain/Model/UserAccessToken.h"
#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/StatusAccessToken.h"
#include "Experience/Model/Cache/ExperienceModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Experience::Domain::Model
{

    FExperienceModelDomain::FExperienceModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ExperienceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Experience::FGs2ExperienceRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ExperienceName(ExperienceName),
        ParentKey(Gs2::Experience::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "ExperienceModel"
        ))
    {
    }

    FExperienceModelDomain::FExperienceModelDomain(
        const FExperienceModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ExperienceName(From.ExperienceName),
        ParentKey(From.ParentKey)
    {

    }

    FExperienceModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FExperienceModelDomain>& Self,
        const Request::FGetExperienceModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FExperienceModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FExperienceModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithExperienceName(Self->ExperienceName);
        const auto Future = Self->Client->GetExperienceModel(
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


        Gs2::Experience::Model::Cache::FExperienceModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetExperienceName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FExperienceModelDomain::FGetTask>> FExperienceModelDomain::Get(
        Request::FGetExperienceModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FExperienceModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ExperienceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ExperienceName.IsSet() ? *ExperienceName : "null") + ":" +
            ChildType;
    }

    FString FExperienceModelDomain::CreateCacheKey(
        TOptional<FString> ExperienceName
    )
    {
        return FString("") +
            (ExperienceName.IsSet() ? *ExperienceName : "null");
    }

    FExperienceModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FExperienceModelDomain> Self
    ): Self(Self)
    {

    }

    FExperienceModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FExperienceModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Experience::Model::Cache::FExperienceModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Experience::Model::Cache::FExperienceModelCache::CreateCacheKey(

            Self->ExperienceName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Experience::Model::FExperienceModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Experience::Model::FExperienceModelPtr Value;
                const auto CacheHit = Gs2::Experience::Model::Cache::FExperienceModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ExperienceName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Experience::Model::Cache::FExperienceModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ExperienceName,
                    TOptional<int32>(),
                    [Self](Gs2::Experience::Model::FExperienceModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Experience::Request::FGetExperienceModelRequest>()
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

    TSharedPtr<FAsyncTask<FExperienceModelDomain::FModelTask>> FExperienceModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FExperienceModelDomain::FModelTask>>(this->AsShared());
    }

    void FExperienceModelDomain::Invalidate()
    {
        Gs2::Experience::Model::Cache::FExperienceModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            ExperienceName,
            TOptional<int32>()
        );
    }

    FExperienceModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FExperienceModelDomain>& Self,
        TFunction<void(Gs2::Experience::Model::FExperienceModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FExperienceModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FExperienceModelDomain::FSubscribeWithInitialCallTask>> FExperienceModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Experience::Model::FExperienceModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FExperienceModelDomain::Subscribe(
        TFunction<void(Gs2::Experience::Model::FExperienceModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Experience::Model::Cache::FExperienceModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Experience::Model::Cache::FExperienceModelCache::CreateCacheKey(

            ExperienceName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Experience::Domain::FGs2ExperienceDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryExperienceName = ExperienceName;
        return Gs2->Cache->Subscribe(
            Gs2::Experience::Model::FExperienceModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Experience::Model::FExperienceModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryExperienceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FExperienceModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryExperienceName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FExperienceModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Experience::Model::Cache::FExperienceModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Experience::Model::Cache::FExperienceModelCache::CreateCacheKey(

            ExperienceName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Experience::Model::FExperienceModel::TypeName,
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
