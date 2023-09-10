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

#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/Namespace.h"
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/MessageAccessToken.h"
#include "Inbox/Domain/Model/CurrentMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessage.h"
#include "Inbox/Domain/Model/Received.h"
#include "Inbox/Domain/Model/ReceivedAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FSendMessageTask::FSendMessageTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FSendMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FSendMessageTask::FSendMessageTask(
        const FSendMessageTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSendMessageTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SendMessageByUserId(
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
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Message"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetExpiresAt().IsSet() && *ResultModel->GetItem()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Inbox::Domain::Model::FMessageDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FSendMessageTask>> FUserDomain::SendMessage(
        Request::FSendMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendMessageTask>>(this->AsShared(), Request);
    }

    FUserDomain::FReceiveGlobalMessageTask::FReceiveGlobalMessageTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FReceiveGlobalMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FReceiveGlobalMessageTask::FReceiveGlobalMessageTask(
        const FReceiveGlobalMessageTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FReceiveGlobalMessageTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->ReceiveGlobalMessageByUserId(
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
            {
                for (auto Item : *ResultModel->GetItem())
                {
                    const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        "Message"
                    );
                    const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                        Item->GetName()
                    );
                    Self->Cache->Put(
                        Gs2::Inbox::Model::FMessage::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        Item->GetExpiresAt().IsSet() ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
            Self->Cache->Delete(
                Gs2::Inbox::Model::FReceived::TypeName,
                Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Received"
                ),
                Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
                )
            );
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>>>();
        for (auto i=0; i<ResultModel->GetItem()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Inbox::Domain::Model::FMessageDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItem())[i]->GetUserId(),
                    (*ResultModel->GetItem())[i]->GetName()
                )
            );
            const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "Message"
            );
            const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                (*ResultModel->GetItem())[i]->GetName()
            );
            Self->Cache->Put(
                Gs2::Inbox::Model::FMessage::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItem())[i],
                (*ResultModel->GetItem())[i]->GetExpiresAt().IsSet() ? FDateTime::FromUnixTimestamp(*(*ResultModel->GetItem())[i]->GetExpiresAt()/1000) :  FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FReceiveGlobalMessageTask>> FUserDomain::ReceiveGlobalMessage(
        Request::FReceiveGlobalMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveGlobalMessageTask>>(this->AsShared(), Request);
    }

    Gs2::Inbox::Domain::Iterator::FDescribeMessagesByUserIdIteratorPtr FUserDomain::Messages(
        const TOptional<bool> IsRead
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Iterator::FDescribeMessagesByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId,
            IsRead
        );
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain> FUserDomain::Message(
        const FString MessageName
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FMessageDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedDomain> FUserDomain::Received(
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FReceivedDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
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

