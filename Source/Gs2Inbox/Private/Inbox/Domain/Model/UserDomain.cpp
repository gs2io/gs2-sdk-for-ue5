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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
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
                Self->Gs2->Cache->Put(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetExpiresAt().IsSet() && *ResultModel->GetItem()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Inbox::Domain::Model::FMessageDomain>(
            Self->Gs2,
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
                    Self->Gs2->Cache->Put(
                        Gs2::Inbox::Model::FMessage::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        Item->GetExpiresAt().IsSet() ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
            Self->Gs2->Cache->Delete(
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
                    Self->Gs2,
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
            Self->Gs2->Cache->Put(
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
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId,
            IsRead
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeMessages(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Message"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeMessages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Message"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain> FUserDomain::Message(
        const FString MessageName
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FMessageDomain>(
            Gs2,
            NamespaceName,
            UserId,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedDomain> FUserDomain::Received(
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FReceivedDomain>(
            Gs2,
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

