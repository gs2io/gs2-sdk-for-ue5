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

#include "SkillTree/Domain/Model/NodeModel.h"
#include "SkillTree/Domain/Model/Namespace.h"
#include "SkillTree/Domain/Model/NodeModel.h"
#include "SkillTree/Domain/Model/NodeModelMaster.h"
#include "SkillTree/Domain/Model/Status.h"
#include "SkillTree/Domain/Model/StatusAccessToken.h"
#include "SkillTree/Domain/Model/CurrentTreeMaster.h"
#include "SkillTree/Domain/Model/User.h"
#include "SkillTree/Domain/Model/UserAccessToken.h"
#include "SkillTree/Model/Cache/NodeModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::SkillTree::Domain::Model
{

    FNodeModelDomain::FNodeModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> NodeModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SkillTree::FGs2SkillTreeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        NodeModelName(NodeModelName),
        ParentKey(Gs2::SkillTree::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "NodeModel"
        ))
    {
    }

    FNodeModelDomain::FNodeModelDomain(
        const FNodeModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        NodeModelName(From.NodeModelName),
        ParentKey(From.ParentKey)
    {

    }

    FNodeModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FNodeModelDomain>& Self,
        const Request::FGetNodeModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNodeModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNodeModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FNodeModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithNodeModelName(Self->NodeModelName);
        const auto Future = Self->Client->GetNodeModel(
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


        Gs2::SkillTree::Model::Cache::FNodeModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetNodeModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNodeModelDomain::FGetTask>> FNodeModelDomain::Get(
        Request::FGetNodeModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FNodeModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> NodeModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (NodeModelName.IsSet() ? *NodeModelName : "null") + ":" +
            ChildType;
    }

    FString FNodeModelDomain::CreateCacheKey(
        TOptional<FString> NodeModelName
    )
    {
        return FString("") +
            (NodeModelName.IsSet() ? *NodeModelName : "null");
    }

    FNodeModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FNodeModelDomain> Self
    ): Self(Self)
    {

    }

    FNodeModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNodeModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SkillTree::Model::FNodeModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::SkillTree::Model::Cache::FNodeModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::SkillTree::Model::Cache::FNodeModelCache::CreateCacheKey(

            Self->NodeModelName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::SkillTree::Model::FNodeModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::SkillTree::Model::FNodeModelPtr Value;
                const auto CacheHit = Gs2::SkillTree::Model::Cache::FNodeModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->NodeModelName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::SkillTree::Model::Cache::FNodeModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->NodeModelName,
                    TOptional<int32>(),
                    [Self](Gs2::SkillTree::Model::FNodeModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::SkillTree::Request::FGetNodeModelRequest>()
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

    TSharedPtr<FAsyncTask<FNodeModelDomain::FModelTask>> FNodeModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNodeModelDomain::FModelTask>>(this->AsShared());
    }

    void FNodeModelDomain::Invalidate()
    {
        Gs2::SkillTree::Model::Cache::FNodeModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            NodeModelName,
            TOptional<int32>()
        );
    }

    FNodeModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FNodeModelDomain>& Self,
        TFunction<void(Gs2::SkillTree::Model::FNodeModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FNodeModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNodeModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FNodeModelDomain::FSubscribeWithInitialCallTask>> FNodeModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::SkillTree::Model::FNodeModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FNodeModelDomain::Subscribe(
        TFunction<void(Gs2::SkillTree::Model::FNodeModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::SkillTree::Model::Cache::FNodeModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SkillTree::Model::Cache::FNodeModelCache::CreateCacheKey(

            NodeModelName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<SkillTree::Domain::FGs2SkillTreeDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryNodeModelName = NodeModelName;
        return Gs2->Cache->Subscribe(
            Gs2::SkillTree::Model::FNodeModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SkillTree::Model::FNodeModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryNodeModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FNodeModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryNodeModelName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FNodeModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::SkillTree::Model::Cache::FNodeModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SkillTree::Model::Cache::FNodeModelCache::CreateCacheKey(

            NodeModelName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::SkillTree::Model::FNodeModel::TypeName,
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
