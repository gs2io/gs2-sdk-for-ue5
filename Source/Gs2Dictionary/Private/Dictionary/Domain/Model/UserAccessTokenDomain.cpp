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

#include "Dictionary/Domain/Model/UserAccessToken.h"
#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/Namespace.h"
#include "Dictionary/Domain/Model/EntryModel.h"
#include "Dictionary/Domain/Model/EntryModelMaster.h"
#include "Dictionary/Domain/Model/Entry.h"
#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Domain/Model/CurrentEntryMaster.h"
#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Dictionary::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Dictionary::FGs2DictionaryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserAccessTokenDomain::FVerifyEntryTask::FVerifyEntryTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FVerifyEntryRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FVerifyEntryTask::FVerifyEntryTask(
        const FVerifyEntryTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FVerifyEntryTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FUserAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->VerifyEntry(
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
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FVerifyEntryTask>> FUserAccessTokenDomain::VerifyEntry(
        Request::FVerifyEntryRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyEntryTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FDeleteEntriesTask::FDeleteEntriesTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FDeleteEntriesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FDeleteEntriesTask::FDeleteEntriesTask(
        const FDeleteEntriesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FDeleteEntriesTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->DeleteEntries(
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
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId(),
                        "Entry"
                    );
                    const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                        Item->GetName()
                    );
                    Self->Gs2->Cache->Delete(
                        Gs2::Dictionary::Model::FEntry::TypeName,
                        ParentKey,
                        Key
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
            const auto ParentKey = Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                "Entry"
            );
            const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Dictionary::Model::FEntry::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FDeleteEntriesTask>> FUserAccessTokenDomain::DeleteEntries(
        Request::FDeleteEntriesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteEntriesTask>>(this->AsShared(), Request);
    }

    Gs2::Dictionary::Domain::Iterator::FDescribeEntriesIteratorPtr FUserAccessTokenDomain::Entries(
    ) const
    {
        return MakeShared<Gs2::Dictionary::Domain::Iterator::FDescribeEntriesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeEntries(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Dictionary::Model::FEntry::TypeName,
            Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Entry"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeEntries(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Dictionary::Model::FEntry::TypeName,
            Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Entry"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain> FUserAccessTokenDomain::Entry(
        const FString EntryName
    )
    {
        return MakeShared<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            EntryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(EntryName)
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

