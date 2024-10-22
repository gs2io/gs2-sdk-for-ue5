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

#include "Quest/Domain/Model/Progress.h"
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

    FProgressDomain::FProgressDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Quest::Domain::FGs2QuestDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Progress"
        ))
    {
    }

    FProgressDomain::FProgressDomain(
        const FProgressDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FProgressDomain::FGetTask::FGetTask(
        const TSharedPtr<FProgressDomain>& Self,
        const Request::FGetProgressByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FProgress>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetProgressByUserId(
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
                    "Progress"
                );
                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FProgress::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetQuestGroup() != nullptr)
            {
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "QuestGroupModel"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheKey(
                    ResultModel->GetQuestGroup()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FQuestGroupModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetQuestGroup(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetQuest() != nullptr)
            {
                const auto ParentKey = Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Gs2::Quest::Model::FQuestModel::GetQuestGroupNameFromGrn(*ResultModel->GetItem()->GetQuestModelId()),
                    "QuestModel"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestModelDomain::CreateCacheKey(
                    ResultModel->GetQuest()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FQuestModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetQuest(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressDomain::FGetTask>> FProgressDomain::Get(
        Request::FGetProgressByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FProgressDomain::FEndTask::FEndTask(
        const TSharedPtr<FProgressDomain>& Self,
        const Request::FEndByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressDomain::FEndTask::FEndTask(
        const FEndTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FEndTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->EndByUserId(
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
                    "Progress"
                );
                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Delete(Gs2::Quest::Model::FProgress::TypeName, ParentKey, Key);
            }
            Self->Gs2->Cache->Delete(
                Gs2::Quest::Model::FCompletedQuestList::TypeName,
                Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "CompletedQuestList"
                ),
                Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                    Gs2::Quest::Model::FQuestModel::GetQuestGroupNameFromGrn(*ResultModel->GetItem()->GetQuestModelId())
                )
            );
            Self->Gs2->Cache->ClearListCache(
                Gs2::Quest::Model::FCompletedQuestList::TypeName,
                Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "CompletedQuestList"
                )
            );
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                *Self->UserId,
                false,
                *ResultModel->GetTransactionId(),
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId()
            );
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressDomain::FEndTask>> FProgressDomain::End(
        Request::FEndByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEndTask>>(this->AsShared(), Request);
    }

    FProgressDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FProgressDomain>& Self,
        const Request::FDeleteProgressByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteProgressByUserId(
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
                    "Progress"
                );
                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Delete(Gs2::Quest::Model::FProgress::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressDomain::FDeleteTask>> FProgressDomain::Delete(
        Request::FDeleteProgressByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FProgressDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FProgressDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FProgressDomain::FModelTask::FModelTask(
        const TSharedPtr<FProgressDomain> Self
    ): Self(Self)
    {

    }

    FProgressDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FProgress>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Quest::Model::FProgress> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Quest::Model::FProgress>(
            Self->ParentKey,
            Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Quest::Request::FGetProgressByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FProgress::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "progress")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Quest::Model::FProgress>(
                Self->ParentKey,
                Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressDomain::FModelTask>> FProgressDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FProgressDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FProgressDomain::Subscribe(
        TFunction<void(Gs2::Quest::Model::FProgressPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Quest::Model::FProgress::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Quest::Model::FProgress>(obj));
            }
        );
    }

    void FProgressDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Quest::Model::FProgress::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
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

