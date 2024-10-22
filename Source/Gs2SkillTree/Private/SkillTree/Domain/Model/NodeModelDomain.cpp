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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::SkillTree::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "NodeModel"
                );
                const auto Key = Gs2::SkillTree::Domain::Model::FNodeModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SkillTree::Model::FNodeModel::TypeName,
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::SkillTree::Model::FNodeModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::SkillTree::Model::FNodeModel>(
            Self->ParentKey,
            Gs2::SkillTree::Domain::Model::FNodeModelDomain::CreateCacheKey(
                Self->NodeModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SkillTree::Request::FGetNodeModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::SkillTree::Domain::Model::FNodeModelDomain::CreateCacheKey(
                    Self->NodeModelName
                );
                Self->Gs2->Cache->Put(
                    Gs2::SkillTree::Model::FNodeModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "nodeModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::SkillTree::Model::FNodeModel>(
                Self->ParentKey,
                Gs2::SkillTree::Domain::Model::FNodeModelDomain::CreateCacheKey(
                    Self->NodeModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNodeModelDomain::FModelTask>> FNodeModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNodeModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNodeModelDomain::Subscribe(
        TFunction<void(Gs2::SkillTree::Model::FNodeModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::SkillTree::Model::FNodeModel::TypeName,
            ParentKey,
            Gs2::SkillTree::Domain::Model::FNodeModelDomain::CreateCacheKey(
                NodeModelName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SkillTree::Model::FNodeModel>(obj));
            }
        );
    }

    void FNodeModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::SkillTree::Model::FNodeModel::TypeName,
            ParentKey,
            Gs2::SkillTree::Domain::Model::FNodeModelDomain::CreateCacheKey(
                NodeModelName
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

