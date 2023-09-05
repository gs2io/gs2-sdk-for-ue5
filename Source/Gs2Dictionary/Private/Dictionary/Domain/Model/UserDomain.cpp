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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/Namespace.h"
#include "Dictionary/Domain/Model/EntryModel.h"
#include "Dictionary/Domain/Model/EntryModelMaster.h"
#include "Dictionary/Domain/Model/Entry.h"
#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Domain/Model/CurrentEntryMaster.h"
#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Dictionary::Domain::Model
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
        Client(MakeShared<Gs2::Dictionary::FGs2DictionaryRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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
        Client(From.Client)
    {

    }

    FUserDomain::FAddEntriesTask::FAddEntriesTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FAddEntriesByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FAddEntriesTask::FAddEntriesTask(
        const FAddEntriesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FAddEntriesTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->AddEntriesByUserId(
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
                        Self->UserId,
                        "Entry"
                    );
                    const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                        Item->GetName()
                    );
                    Self->Cache->Put(
                        Gs2::Dictionary::Model::FEntry::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Dictionary::Domain::Model::FEntryDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
            const auto ParentKey = Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "Entry"
            );
            const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetName()
            );
            Self->Cache->Put(
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

    TSharedPtr<FAsyncTask<FUserDomain::FAddEntriesTask>> FUserDomain::AddEntries(
        Request::FAddEntriesByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddEntriesTask>>(this->AsShared(), Request);
    }

    FUserDomain::FResetTask::FResetTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FResetByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FResetTask::FResetTask(
        const FResetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FResetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->ResetByUserId(
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
            
            const auto ParentKey = CreateCacheParentKey(
                RequestModel->GetNamespaceName(),
                RequestModel->GetUserId(),
                "Entry"
            );
            auto List = Self->Cache->TryGetList<Gs2::Dictionary::Model::FEntry>(ParentKey);
            if (List)
            {
                for (auto Item : *List) {
                    Self->Cache->Delete(
                        Gs2::Dictionary::Model::FEntry::TypeName,
                        ParentKey,
                        Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                            Item->GetName()
                        )
                    );
                }
            }
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FResetTask>> FUserDomain::Reset(
        Request::FResetByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FResetTask>>(this->AsShared(), Request);
    }

    FUserDomain::FDeleteEntriesTask::FDeleteEntriesTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FDeleteEntriesByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDeleteEntriesTask::FDeleteEntriesTask(
        const FDeleteEntriesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDeleteEntriesTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteEntriesByUserId(
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
                        Self->UserId,
                        "Entry"
                    );
                    const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                        Item->GetName()
                    );
                    Self->Cache->Delete(
                        Gs2::Dictionary::Model::FEntry::TypeName,
                        ParentKey,
                        Key
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>>>();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FDeleteEntriesTask>> FUserDomain::DeleteEntries(
        Request::FDeleteEntriesByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteEntriesTask>>(this->AsShared(), Request);
    }

    Gs2::Dictionary::Domain::Iterator::FDescribeEntriesByUserIdIteratorPtr FUserDomain::Entries(
    ) const
    {
        return MakeShared<Gs2::Dictionary::Domain::Iterator::FDescribeEntriesByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain> FUserDomain::Entry(
        const FString EntryName
    ) const
    {
        return MakeShared<Gs2::Dictionary::Domain::Model::FEntryDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            EntryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(EntryName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString() +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

