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

#include "Grade/Domain/Model/GradeModel.h"
#include "Grade/Domain/Model/Namespace.h"
#include "Grade/Domain/Model/GradeModelMaster.h"
#include "Grade/Domain/Model/GradeModel.h"
#include "Grade/Domain/Model/User.h"
#include "Grade/Domain/Model/UserAccessToken.h"
#include "Grade/Domain/Model/Status.h"
#include "Grade/Domain/Model/StatusAccessToken.h"
#include "Grade/Domain/Model/CurrentGradeMaster.h"
#include "Grade/Model/Cache/GradeModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Grade::Domain::Model
{

    FGradeModelDomain::FGradeModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Grade::Domain::FGs2GradeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GradeName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Grade::FGs2GradeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GradeName(GradeName),
        ParentKey(Gs2::Grade::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "GradeModel"
        ))
    {
    }

    FGradeModelDomain::FGradeModelDomain(
        const FGradeModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GradeName(From.GradeName),
        ParentKey(From.ParentKey)
    {

    }

    FGradeModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FGradeModelDomain>& Self,
        const Request::FGetGradeModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGradeModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGradeModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Model::FGradeModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGradeName(Self->GradeName);
        const auto Future = Self->Client->GetGradeModel(
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


        Gs2::Grade::Model::Cache::FGradeModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetGradeName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGradeModelDomain::FGetTask>> FGradeModelDomain::Get(
        Request::FGetGradeModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FGradeModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GradeName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GradeName.IsSet() ? *GradeName : "null") + ":" +
            ChildType;
    }

    FString FGradeModelDomain::CreateCacheKey(
        TOptional<FString> GradeName
    )
    {
        return FString("") +
            (GradeName.IsSet() ? *GradeName : "null");
    }

    FGradeModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FGradeModelDomain> Self
    ): Self(Self)
    {

    }

    FGradeModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGradeModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Model::FGradeModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Grade::Model::Cache::FGradeModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Grade::Model::Cache::FGradeModelCache::CreateCacheKey(

            Self->GradeName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Grade::Model::FGradeModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Grade::Model::FGradeModelPtr Value;
                const auto CacheHit = Gs2::Grade::Model::Cache::FGradeModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->GradeName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Grade::Model::Cache::FGradeModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->GradeName,
                    TOptional<int32>(),
                    [Self](Gs2::Grade::Model::FGradeModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Grade::Request::FGetGradeModelRequest>()
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

    TSharedPtr<FAsyncTask<FGradeModelDomain::FModelTask>> FGradeModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGradeModelDomain::FModelTask>>(this->AsShared());
    }

    void FGradeModelDomain::Invalidate()
    {
        Gs2::Grade::Model::Cache::FGradeModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            GradeName,
            TOptional<int32>()
        );
    }

    FGradeModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FGradeModelDomain>& Self,
        TFunction<void(Gs2::Grade::Model::FGradeModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FGradeModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGradeModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FGradeModelDomain::FSubscribeWithInitialCallTask>> FGradeModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Grade::Model::FGradeModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FGradeModelDomain::Subscribe(
        TFunction<void(Gs2::Grade::Model::FGradeModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Grade::Model::Cache::FGradeModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Grade::Model::Cache::FGradeModelCache::CreateCacheKey(

            GradeName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Grade::Domain::FGs2GradeDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryGradeName = GradeName;
        return Gs2->Cache->Subscribe(
            Gs2::Grade::Model::FGradeModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Grade::Model::FGradeModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryGradeName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FGradeModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryGradeName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FGradeModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Grade::Model::Cache::FGradeModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Grade::Model::Cache::FGradeModelCache::CreateCacheKey(

            GradeName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Grade::Model::FGradeModel::TypeName,
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
