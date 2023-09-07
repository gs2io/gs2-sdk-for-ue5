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

#include "Inbox/Domain/Model/UserAccessToken.h"
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

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FUserAccessTokenDomain::FReceiveGlobalMessageTask::FReceiveGlobalMessageTask(
        const TSharedPtr<FUserAccessTokenDomain> Self,
        const Request::FReceiveGlobalMessageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FReceiveGlobalMessageTask::FReceiveGlobalMessageTask(
        const FReceiveGlobalMessageTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FReceiveGlobalMessageTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->ReceiveGlobalMessage(
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
                        Self->UserId(),
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
                    Self->UserId(),
                    "Received"
                ),
                Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
                )
            );
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>>>();
        for (auto i=0; i<ResultModel->GetItem()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
                    (*ResultModel->GetItem())[i]->GetName()
                )
            );
            const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
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

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FReceiveGlobalMessageTask>> FUserAccessTokenDomain::ReceiveGlobalMessage(
        Request::FReceiveGlobalMessageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveGlobalMessageTask>>(this->AsShared(), Request);
    }

    Gs2::Inbox::Domain::Iterator::FDescribeMessagesIteratorPtr FUserAccessTokenDomain::Messages(
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Iterator::FDescribeMessagesIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain> FUserAccessTokenDomain::Message(
        const FString MessageName
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedAccessTokenDomain> FUserAccessTokenDomain::Received(
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FReceivedAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
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

