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

#include "Distributor/Domain/Model/DistributorModel.h"
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

    FDistributorModelDomain::FDistributorModelDomain(
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
            "DistributorModel"
        ))
    {
    }

    FDistributorModelDomain::FDistributorModelDomain(
        const FDistributorModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FDistributorModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FDistributorModelDomain> Self,
        const Request::FGetDistributorModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDistributorModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDistributorModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FDistributorModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDistributorName(Self->DistributorName);
        const auto Future = Self->Client->GetDistributorModel(
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
                    "DistributorModel"
                );
                const auto Key = Gs2::Distributor::Domain::Model::FDistributorModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Distributor::Model::FDistributorModel>(
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

    TSharedPtr<FAsyncTask<FDistributorModelDomain::FGetTask>> FDistributorModelDomain::Get(
        Request::FGetDistributorModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FDistributorModelDomain::CreateCacheParentKey(
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

    FString FDistributorModelDomain::CreateCacheKey(
        TOptional<FString> DistributorName
    )
    {
        return FString() +
            (DistributorName.IsSet() ? *DistributorName : "null");
    }

    FDistributorModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FDistributorModelDomain> Self
    ): Self(Self)
    {

    }

    FDistributorModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDistributorModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FDistributorModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Distributor::Model::FDistributorModel>(
            Self->ParentKey,
            Gs2::Distributor::Domain::Model::FDistributorModelDomain::CreateCacheKey(
                Self->DistributorName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Distributor::Request::FGetDistributorModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "distributorModel")
                    {
                        Self->Cache->Delete<Gs2::Distributor::Model::FDistributorModel>(
                            Self->ParentKey,
                            Gs2::Distributor::Domain::Model::FDistributorModelDomain::CreateCacheKey(
                                Self->DistributorName
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
            Value = Self->Cache->Get<Gs2::Distributor::Model::FDistributorModel>(
                Self->ParentKey,
                Gs2::Distributor::Domain::Model::FDistributorModelDomain::CreateCacheKey(
                    Self->DistributorName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDistributorModelDomain::FModelTask>> FDistributorModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDistributorModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

