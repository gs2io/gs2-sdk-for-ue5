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

#include "Showcase/Domain/Model/SalesItemGroupMaster.h"
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

    FSalesItemGroupMasterDomain::FSalesItemGroupMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> SalesItemGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Session)),
        NamespaceName(NamespaceName),
        SalesItemGroupName(SalesItemGroupName),
        ParentKey(Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "SalesItemGroupMaster"
        ))
    {
    }

    FSalesItemGroupMasterDomain::FSalesItemGroupMasterDomain(
        const FSalesItemGroupMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FSalesItemGroupMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FSalesItemGroupMasterDomain> Self,
        const Request::FGetSalesItemGroupMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSalesItemGroupMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSalesItemGroupMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FSalesItemGroupMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSalesItemGroupName(Self->SalesItemGroupName);
        const auto Future = Self->Client->GetSalesItemGroupMaster(
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
                    "SalesItemGroupMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Showcase::Model::FSalesItemGroupMaster>(
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

    TSharedPtr<FAsyncTask<FSalesItemGroupMasterDomain::FGetTask>> FSalesItemGroupMasterDomain::Get(
        Request::FGetSalesItemGroupMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSalesItemGroupMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FSalesItemGroupMasterDomain> Self,
        const Request::FUpdateSalesItemGroupMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSalesItemGroupMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSalesItemGroupMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSalesItemGroupName(Self->SalesItemGroupName);
        const auto Future = Self->Client->UpdateSalesItemGroupMaster(
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
                    "SalesItemGroupMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Showcase::Model::FSalesItemGroupMaster>(
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

    TSharedPtr<FAsyncTask<FSalesItemGroupMasterDomain::FUpdateTask>> FSalesItemGroupMasterDomain::Update(
        Request::FUpdateSalesItemGroupMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FSalesItemGroupMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FSalesItemGroupMasterDomain> Self,
        const Request::FDeleteSalesItemGroupMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSalesItemGroupMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSalesItemGroupMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSalesItemGroupName(Self->SalesItemGroupName);
        const auto Future = Self->Client->DeleteSalesItemGroupMaster(
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
                    "SalesItemGroupMaster"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete<Gs2::Showcase::Model::FSalesItemGroupMaster>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSalesItemGroupMasterDomain::FDeleteTask>> FSalesItemGroupMasterDomain::Delete(
        Request::FDeleteSalesItemGroupMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FSalesItemGroupMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> SalesItemGroupName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (SalesItemGroupName.IsSet() ? *SalesItemGroupName : "null") + ":" +
            ChildType;
    }

    FString FSalesItemGroupMasterDomain::CreateCacheKey(
        TOptional<FString> SalesItemGroupName
    )
    {
        return FString() +
            (SalesItemGroupName.IsSet() ? *SalesItemGroupName : "null");
    }

    FSalesItemGroupMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FSalesItemGroupMasterDomain> Self
    ): Self(Self)
    {

    }

    FSalesItemGroupMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSalesItemGroupMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FSalesItemGroupMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Showcase::Model::FSalesItemGroupMaster>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain::CreateCacheKey(
                Self->SalesItemGroupName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Showcase::Request::FGetSalesItemGroupMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "salesItemGroupMaster")
                    {
                        Self->Cache->Delete<Gs2::Showcase::Model::FSalesItemGroupMaster>(
                            Self->ParentKey,
                            Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain::CreateCacheKey(
                                Self->SalesItemGroupName
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
            Value = Self->Cache->Get<Gs2::Showcase::Model::FSalesItemGroupMaster>(
                Self->ParentKey,
                Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain::CreateCacheKey(
                    Self->SalesItemGroupName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSalesItemGroupMasterDomain::FModelTask>> FSalesItemGroupMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSalesItemGroupMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

