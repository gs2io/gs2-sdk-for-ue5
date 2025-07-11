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

#include "Quest/Domain/Model/UserAccessToken.h"
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
#include "Quest/Domain/SpeculativeExecutor/Transaction/StartByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Quest::Domain::FGs2QuestDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FUserAccessTokenDomain::FStartTask::FStartTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FStartRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FUserAccessTokenDomain::FStartTask::FStartTask(
        const FStartTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FStartTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->Start(
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
            Self->AccessToken,
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

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FStartTask>> FUserAccessTokenDomain::Start(
        Request::FStartRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FStartTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIteratorPtr FUserAccessTokenDomain::CompletedQuestLists(
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeCompletedQuestLists(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Quest::Model::FCompletedQuestList::TypeName,
            Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "CompletedQuestList"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeCompletedQuestLists(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Quest::Model::FCompletedQuestList::TypeName,
            Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "CompletedQuestList"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Quest::Domain::Model::FCompletedQuestListAccessTokenDomain> FUserAccessTokenDomain::CompletedQuestList(
        const FString QuestGroupName
    )
    {
        return MakeShared<Gs2::Quest::Domain::Model::FCompletedQuestListAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            QuestGroupName == TEXT("") ? TOptional<FString>() : TOptional<FString>(QuestGroupName)
        );
    }

    TSharedPtr<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain> FUserAccessTokenDomain::Progress(
    )
    {
        return MakeShared<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
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

    FString FUserAccessTokenDomain::CreateCacheKey(
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

