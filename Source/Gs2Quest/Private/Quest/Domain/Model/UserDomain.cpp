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

#include "Quest/Domain/Model/User.h"
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

    FUserDomain::FUserDomain(
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
        ParentKey(Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FCreateProgressTask::FCreateProgressTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FCreateProgressByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FCreateProgressTask::FCreateProgressTask(
        const FCreateProgressTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FCreateProgressTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->CreateProgressByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Quest::Domain::Model::FProgressDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FCreateProgressTask>> FUserDomain::CreateProgress(
        Request::FCreateProgressByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateProgressTask>>(this->AsShared(), Request);
    }

    FUserDomain::FStartTask::FStartTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FStartByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FStartTask::FStartTask(
        const FStartTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FStartTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->StartByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            *ResultModel->GetTransactionId(),
            *ResultModel->GetStampSheet(),
            *ResultModel->GetStampSheetEncryptionKeyId(),
            *ResultModel->GetAtomicCommit(),
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FStartTask>> FUserDomain::Start(
        Request::FStartByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FStartTask>>(this->AsShared(), Request);
    }

    Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsByUserIdIteratorPtr FUserDomain::CompletedQuestLists(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeCompletedQuestLists(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Quest::Model::FCompletedQuestList::TypeName,
            Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "CompletedQuestList"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeCompletedQuestLists(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Quest::Model::FCompletedQuestList::TypeName,
            Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "CompletedQuestList"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Quest::Domain::Model::FCompletedQuestListDomain> FUserDomain::CompletedQuestList(
        const FString QuestGroupName
    )
    {
        return MakeShared<Gs2::Quest::Domain::Model::FCompletedQuestListDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            QuestGroupName == TEXT("") ? TOptional<FString>() : TOptional<FString>(QuestGroupName)
        );
    }

    Gs2::Quest::Domain::Iterator::FDescribeProgressesByUserIdIteratorPtr FUserDomain::Progresses(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Iterator::FDescribeProgressesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeProgresses(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Quest::Model::FProgress::TypeName,
            Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Progress"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeProgresses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Quest::Model::FProgress::TypeName,
            Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Progress"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Quest::Domain::Model::FProgressDomain> FUserDomain::Progress(
    )
    {
        return MakeShared<Gs2::Quest::Domain::Model::FProgressDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

