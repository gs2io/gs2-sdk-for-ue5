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

#include "Dictionary/Domain/Model/Entry.h"
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

    FEntryDomain::FEntryDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> EntryModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Dictionary::FGs2DictionaryRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        EntryModelName(EntryModelName),
        ParentKey(Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Entry"
        ))
    {
    }

    FEntryDomain::FEntryDomain(
        const FEntryDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FEntryDomain::FGetTask::FGetTask(
        const TSharedPtr<FEntryDomain> Self,
        const Request::FGetEntryByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEntryDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntry>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithEntryModelName(Self->EntryModelName);
        const auto Future = Self->Client->GetEntryByUserId(
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
                const auto ParentKey = Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Entry"
                );
                const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FEntry::TypeName,
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

    TSharedPtr<FAsyncTask<FEntryDomain::FGetTask>> FEntryDomain::Get(
        Request::FGetEntryByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FEntryDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const TSharedPtr<FEntryDomain> Self,
        const Request::FGetEntryWithSignatureByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEntryDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const FGetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryDomain::FGetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithEntryModelName(Self->EntryModelName);
        const auto Future = Self->Client->GetEntryWithSignatureByUserId(
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
                const auto ParentKey = Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Entry"
                );
                const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FEntry::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        Domain->Body = *ResultModel->GetBody();
        Domain->Signature = *ResultModel->GetSignature();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryDomain::FGetWithSignatureTask>> FEntryDomain::GetWithSignature(
        Request::FGetEntryWithSignatureByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetWithSignatureTask>>(this->AsShared(), Request);
    }

    FString FEntryDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> EntryModelName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (EntryModelName.IsSet() ? *EntryModelName : "null") + ":" +
            ChildType;
    }

    FString FEntryDomain::CreateCacheKey(
        TOptional<FString> EntryModelName
    )
    {
        return FString() +
            (EntryModelName.IsSet() ? *EntryModelName : "null");
    }

    FEntryDomain::FModelTask::FModelTask(
        const TSharedPtr<FEntryDomain> Self
    ): Self(Self)
    {

    }

    FEntryDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntry>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Dictionary::Model::FEntry>(
            Self->ParentKey,
            Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                Self->EntryModelName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Dictionary::Request::FGetEntryByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "entry")
                    {
                        Self->Cache->Delete(
                            Gs2::Dictionary::Model::FEntry::TypeName,
                            Self->ParentKey,
                            Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                                Self->EntryModelName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Dictionary::Model::FEntry>(
                Self->ParentKey,
                Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                    Self->EntryModelName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryDomain::FModelTask>> FEntryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FEntryDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

