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

#include "Quest/Domain/Model/QuestGroupModel.h"
#include "Quest/Domain/Model/Namespace.h"
#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/QuestModelMaster.h"
#include "Quest/Domain/Model/CurrentQuestMaster.h"
#include "Quest/Domain/Model/Progress.h"
#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Domain/Model/CompletedQuestList.h"
#include "Quest/Domain/Model/CompletedQuestListAccessToken.h"
#include "Quest/Domain/Model/QuestGroupModel.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/User.h"
#include "Quest/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FQuestGroupModelDomain::FQuestGroupModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Quest::Domain::FGs2QuestDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> QuestGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        QuestGroupName(QuestGroupName),
        ParentKey(Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "QuestGroupModel"
        ))
    {
    }

    FQuestGroupModelDomain::FQuestGroupModelDomain(
        const FQuestGroupModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        QuestGroupName(From.QuestGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FQuestGroupModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FQuestGroupModelDomain>& Self,
        const Request::FGetQuestGroupModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->GetQuestGroupModel(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "QuestGroupModel"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FQuestGroupModel::TypeName,
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

    TSharedPtr<FAsyncTask<FQuestGroupModelDomain::FGetTask>> FQuestGroupModelDomain::Get(
        Request::FGetQuestGroupModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIteratorPtr FQuestGroupModelDomain::QuestModels(
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator>(
            Gs2,
            Client,
            NamespaceName,
            QuestGroupName
        );
    }

    Gs2::Core::Domain::CallbackID FQuestGroupModelDomain::SubscribeQuestModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Quest::Model::FQuestModel::TypeName,
            Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheParentKey(
                NamespaceName,
                QuestGroupName,
                "QuestModel"
            ),
            Callback
        );
    }

    void FQuestGroupModelDomain::UnsubscribeQuestModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Quest::Model::FQuestModel::TypeName,
            Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheParentKey(
                NamespaceName,
                QuestGroupName,
                "QuestModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelDomain> FQuestGroupModelDomain::QuestModel(
        const FString QuestName
    )
    {
        return MakeShared<Gs2::Quest::Domain::Model::FQuestModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            QuestGroupName,
            QuestName == TEXT("") ? TOptional<FString>() : TOptional<FString>(QuestName)
        );
    }

    FString FQuestGroupModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> QuestGroupName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null") + ":" +
            ChildType;
    }

    FString FQuestGroupModelDomain::CreateCacheKey(
        TOptional<FString> QuestGroupName
    )
    {
        return FString("") +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null");
    }

    FQuestGroupModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FQuestGroupModelDomain> Self
    ): Self(Self)
    {

    }

    FQuestGroupModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Quest::Model::FQuestGroupModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Quest::Model::FQuestGroupModel>(
            Self->ParentKey,
            Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheKey(
                Self->QuestGroupName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Quest::Request::FGetQuestGroupModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheKey(
                    Self->QuestGroupName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FQuestGroupModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "questGroupModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Quest::Model::FQuestGroupModel>(
                Self->ParentKey,
                Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheKey(
                    Self->QuestGroupName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestGroupModelDomain::FModelTask>> FQuestGroupModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FQuestGroupModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FQuestGroupModelDomain::Subscribe(
        TFunction<void(Gs2::Quest::Model::FQuestGroupModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Quest::Model::FQuestGroupModel::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheKey(
                QuestGroupName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Quest::Model::FQuestGroupModel>(obj));
            }
        );
    }

    void FQuestGroupModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Quest::Model::FQuestGroupModel::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheKey(
                QuestGroupName
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

