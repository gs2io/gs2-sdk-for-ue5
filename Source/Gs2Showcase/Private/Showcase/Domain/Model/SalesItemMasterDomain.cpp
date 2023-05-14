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

#include "Showcase/Domain/Model/SalesItemMaster.h"
#include "Showcase/Domain/Model/Namespace.h"
#include "Showcase/Domain/Model/SalesItemMaster.h"
#include "Showcase/Domain/Model/SalesItemGroupMaster.h"
#include "Showcase/Domain/Model/ShowcaseMaster.h"
#include "Showcase/Domain/Model/CurrentShowcaseMaster.h"
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Domain/Model/ShowcaseAccessToken.h"
#include "Showcase/Domain/Model/User.h"
#include "Showcase/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FSalesItemMasterDomain::FSalesItemMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> SalesItemName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Session)),
        NamespaceName(NamespaceName),
        SalesItemName(SalesItemName),
        ParentKey(Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "SalesItemMaster"
        ))
    {
    }

    FSalesItemMasterDomain::FSalesItemMasterDomain(
        const FSalesItemMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FSalesItemMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FSalesItemMasterDomain> Self,
        const Request::FGetSalesItemMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSalesItemMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSalesItemMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FSalesItemMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSalesItemName(Self->SalesItemName);
        const auto Future = Self->Client->GetSalesItemMaster(
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "SalesItemMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FSalesItemMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FSalesItemMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FSalesItemMasterDomain::FGetTask>> FSalesItemMasterDomain::Get(
        Request::FGetSalesItemMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSalesItemMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FSalesItemMasterDomain> Self,
        const Request::FUpdateSalesItemMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSalesItemMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSalesItemMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSalesItemName(Self->SalesItemName);
        const auto Future = Self->Client->UpdateSalesItemMaster(
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "SalesItemMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FSalesItemMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FSalesItemMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSalesItemMasterDomain::FUpdateTask>> FSalesItemMasterDomain::Update(
        Request::FUpdateSalesItemMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FSalesItemMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FSalesItemMasterDomain> Self,
        const Request::FDeleteSalesItemMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSalesItemMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSalesItemMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSalesItemName(Self->SalesItemName);
        const auto Future = Self->Client->DeleteSalesItemMaster(
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "SalesItemMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FSalesItemMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Showcase::Model::FSalesItemMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSalesItemMasterDomain::FDeleteTask>> FSalesItemMasterDomain::Delete(
        Request::FDeleteSalesItemMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FSalesItemMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> SalesItemName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (SalesItemName.IsSet() ? *SalesItemName : "null") + ":" +
            ChildType;
    }

    FString FSalesItemMasterDomain::CreateCacheKey(
        TOptional<FString> SalesItemName
    )
    {
        return FString() +
            (SalesItemName.IsSet() ? *SalesItemName : "null");
    }

    FSalesItemMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FSalesItemMasterDomain> Self
    ): Self(Self)
    {

    }

    FSalesItemMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSalesItemMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FSalesItemMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Showcase::Model::FSalesItemMaster>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FSalesItemMasterDomain::CreateCacheKey(
                Self->SalesItemName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Showcase::Request::FGetSalesItemMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "salesItemMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::Showcase::Model::FSalesItemMaster::TypeName,
                            Self->ParentKey,
                            Gs2::Showcase::Domain::Model::FSalesItemMasterDomain::CreateCacheKey(
                                Self->SalesItemName
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
            Value = Self->Cache->Get<Gs2::Showcase::Model::FSalesItemMaster>(
                Self->ParentKey,
                Gs2::Showcase::Domain::Model::FSalesItemMasterDomain::CreateCacheKey(
                    Self->SalesItemName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSalesItemMasterDomain::FModelTask>> FSalesItemMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSalesItemMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

