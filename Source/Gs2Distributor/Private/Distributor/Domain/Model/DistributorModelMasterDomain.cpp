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

#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Distributor::Domain::Model
{

    FDistributorModelMasterDomain::FDistributorModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> DistributorName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Session)),
        NamespaceName(NamespaceName),
        DistributorName(DistributorName),
        ParentKey(Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "DistributorModelMaster"
        ))
    {
    }

    FDistributorModelMasterDomain::FDistributorModelMasterDomain(
        const FDistributorModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FDistributorModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FDistributorModelMasterDomain> Self,
        const Request::FGetDistributorModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDistributorModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDistributorModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FDistributorModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDistributorName(Self->DistributorName);
        const auto Future = Self->Client->GetDistributorModelMaster(
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
                const auto ParentKey = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "DistributorModelMaster"
                );
                const auto Key = Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FDistributorModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FDistributorModelMasterDomain::FGetTask>> FDistributorModelMasterDomain::Get(
        Request::FGetDistributorModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FDistributorModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FDistributorModelMasterDomain> Self,
        const Request::FUpdateDistributorModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDistributorModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDistributorModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDistributorName(Self->DistributorName);
        const auto Future = Self->Client->UpdateDistributorModelMaster(
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
                const auto ParentKey = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "DistributorModelMaster"
                );
                const auto Key = Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FDistributorModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FDistributorModelMasterDomain::FUpdateTask>> FDistributorModelMasterDomain::Update(
        Request::FUpdateDistributorModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FDistributorModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FDistributorModelMasterDomain> Self,
        const Request::FDeleteDistributorModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDistributorModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDistributorModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDistributorName(Self->DistributorName);
        const auto Future = Self->Client->DeleteDistributorModelMaster(
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
                const auto ParentKey = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "DistributorModelMaster"
                );
                const auto Key = Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Distributor::Model::FDistributorModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDistributorModelMasterDomain::FDeleteTask>> FDistributorModelMasterDomain::Delete(
        Request::FDeleteDistributorModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FDistributorModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> DistributorName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (DistributorName.IsSet() ? *DistributorName : "null") + ":" +
            ChildType;
    }

    FString FDistributorModelMasterDomain::CreateCacheKey(
        TOptional<FString> DistributorName
    )
    {
        return FString() +
            (DistributorName.IsSet() ? *DistributorName : "null");
    }

    FDistributorModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FDistributorModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FDistributorModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDistributorModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FDistributorModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Distributor::Model::FDistributorModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Distributor::Model::FDistributorModelMaster>(
            Self->ParentKey,
            Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain::CreateCacheKey(
                Self->DistributorName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Distributor::Request::FGetDistributorModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain::CreateCacheKey(
                    Self->DistributorName
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FDistributorModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "distributorModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Distributor::Model::FDistributorModelMaster>(
                Self->ParentKey,
                Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain::CreateCacheKey(
                    Self->DistributorName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDistributorModelMasterDomain::FModelTask>> FDistributorModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDistributorModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

