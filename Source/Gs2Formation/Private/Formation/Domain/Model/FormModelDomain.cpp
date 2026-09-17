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

#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"
#include "Formation/Model/Cache/FormModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FFormModelDomain::FFormModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Formation::Domain::FGs2FormationDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MoldModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        MoldModelName(MoldModelName),
        ParentKey(Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheParentKey(
            NamespaceName,
            MoldModelName,
            "FormModel"
        ))
    {
    }

    FFormModelDomain::FFormModelDomain(
        const FFormModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        MoldModelName(From.MoldModelName),
        ParentKey(From.ParentKey)
    {

    }

    FFormModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FFormModelDomain>& Self,
        const Request::FGetFormModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FFormModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->GetFormModel(
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


        Gs2::Formation::Model::Cache::FFormModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormModelDomain::FGetTask>> FFormModelDomain::Get(
        Request::FGetFormModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FFormModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MoldModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MoldModelName.IsSet() ? *MoldModelName : "null") + ":" +
            ChildType;
    }

    FString FFormModelDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FFormModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FFormModelDomain> Self
    ): Self(Self)
    {

    }

    FFormModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFormModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FFormModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Formation::Model::Cache::FFormModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->MoldModelName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Formation::Model::Cache::FFormModelCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Formation::Model::FFormModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Formation::Model::FFormModelPtr Value;
                const auto CacheHit = Gs2::Formation::Model::Cache::FFormModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->MoldModelName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Formation::Model::Cache::FFormModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->MoldModelName,
                    TOptional<int32>(),
                    [Self](Gs2::Formation::Model::FFormModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Formation::Request::FGetFormModelRequest>()
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

    TSharedPtr<FAsyncTask<FFormModelDomain::FModelTask>> FFormModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFormModelDomain::FModelTask>>(this->AsShared());
    }

    void FFormModelDomain::Invalidate()
    {
        Gs2::Formation::Model::Cache::FFormModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            MoldModelName,
            TOptional<int32>()
        );
    }

    FFormModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FFormModelDomain>& Self,
        TFunction<void(Gs2::Formation::Model::FFormModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FFormModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FFormModelDomain::FSubscribeWithInitialCallTask>> FFormModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Formation::Model::FFormModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FFormModelDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FFormModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Formation::Model::Cache::FFormModelCache::CreateCacheParentKey(

            NamespaceName,
            MoldModelName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Formation::Model::Cache::FFormModelCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Formation::Domain::FGs2FormationDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryMoldModelName = MoldModelName;
        return Gs2->Cache->Subscribe(
            Gs2::Formation::Model::FFormModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FFormModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryMoldModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FFormModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryMoldModelName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FFormModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Formation::Model::Cache::FFormModelCache::CreateCacheParentKey(

            NamespaceName,
            MoldModelName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Formation::Model::Cache::FFormModelCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Formation::Model::FFormModel::TypeName,
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
