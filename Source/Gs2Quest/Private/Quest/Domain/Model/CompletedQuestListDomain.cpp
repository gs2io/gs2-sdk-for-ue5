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

#include "Quest/Domain/Model/CompletedQuestList.h"
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

    FCompletedQuestListDomain::FCompletedQuestListDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Quest::Domain::FGs2QuestDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> QuestGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        QuestGroupName(QuestGroupName),
        ParentKey(Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "CompletedQuestList"
        ))
    {
    }

    FCompletedQuestListDomain::FCompletedQuestListDomain(
        const FCompletedQuestListDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        QuestGroupName(From.QuestGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FCompletedQuestListDomain::FGetTask::FGetTask(
        const TSharedPtr<FCompletedQuestListDomain>& Self,
        const Request::FGetCompletedQuestListByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompletedQuestListDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompletedQuestListDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FCompletedQuestList>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetCompletedQuestListByUserId(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "CompletedQuestList"
                );
                const auto Key = Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetQuestGroupName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FCompletedQuestList::TypeName,
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

    TSharedPtr<FAsyncTask<FCompletedQuestListDomain::FGetTask>> FCompletedQuestListDomain::Get(
        Request::FGetCompletedQuestListByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCompletedQuestListDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FCompletedQuestListDomain>& Self,
        const Request::FDeleteCompletedQuestListByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompletedQuestListDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompletedQuestListDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FCompletedQuestListDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteCompletedQuestListByUserId(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "CompletedQuestList"
                );
                const auto Key = Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetQuestGroupName()
                );
                Self->Gs2->Cache->Delete(Gs2::Quest::Model::FCompletedQuestList::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompletedQuestListDomain::FDeleteTask>> FCompletedQuestListDomain::Delete(
        Request::FDeleteCompletedQuestListByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FCompletedQuestListDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> QuestGroupName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null") + ":" +
            ChildType;
    }

    FString FCompletedQuestListDomain::CreateCacheKey(
        TOptional<FString> QuestGroupName
    )
    {
        return FString("") +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null");
    }

    FCompletedQuestListDomain::FModelTask::FModelTask(
        const TSharedPtr<FCompletedQuestListDomain> Self
    ): Self(Self)
    {

    }

    FCompletedQuestListDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCompletedQuestListDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FCompletedQuestList>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Quest::Model::FCompletedQuestList> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Quest::Model::FCompletedQuestList>(
            Self->ParentKey,
            Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                Self->QuestGroupName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Quest::Request::FGetCompletedQuestListByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                    Self->QuestGroupName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FCompletedQuestList::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "completedQuestList")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Quest::Model::FCompletedQuestList>(
                Self->ParentKey,
                Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                    Self->QuestGroupName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompletedQuestListDomain::FModelTask>> FCompletedQuestListDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCompletedQuestListDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCompletedQuestListDomain::Subscribe(
        TFunction<void(Gs2::Quest::Model::FCompletedQuestListPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Quest::Model::FCompletedQuestList::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                QuestGroupName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Quest::Model::FCompletedQuestList>(obj));
            }
        );
    }

    void FCompletedQuestListDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Quest::Model::FCompletedQuestList::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
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

