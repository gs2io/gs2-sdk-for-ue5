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

#include "SerialKey/Domain/Model/CampaignModel.h"
#include "SerialKey/Domain/Model/Namespace.h"
#include "SerialKey/Domain/Model/IssueJob.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/SerialKeyAccessToken.h"
#include "SerialKey/Domain/Model/User.h"
#include "SerialKey/Domain/Model/UserAccessToken.h"
#include "SerialKey/Domain/Model/CampaignModel.h"
#include "SerialKey/Domain/Model/CampaignModelMaster.h"
#include "SerialKey/Domain/Model/CurrentCampaignMaster.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::SerialKey::Domain::Model
{

    FCampaignModelDomain::FCampaignModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CampaignModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Session)),
        NamespaceName(NamespaceName),
        CampaignModelName(CampaignModelName),
        ParentKey(Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CampaignModel"
        ))
    {
    }

    FCampaignModelDomain::FCampaignModelDomain(
        const FCampaignModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCampaignModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FCampaignModelDomain> Self,
        const Request::FGetCampaignModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCampaignModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCampaignModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCampaignModelName(Self->CampaignModelName);
        const auto Future = Self->Client->GetCampaignModel(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CampaignModel"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCampaignModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::SerialKey::Model::FCampaignModel>(
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

    TSharedPtr<FAsyncTask<FCampaignModelDomain::FGetTask>> FCampaignModelDomain::Get(
        Request::FGetCampaignModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCampaignModelDomain::FIssueTask::FIssueTask(
        const TSharedPtr<FCampaignModelDomain> Self,
        const Request::FIssueRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCampaignModelDomain::FIssueTask::FIssueTask(
        const FIssueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelDomain::FIssueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FIssueJobDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCampaignModelName(Self->CampaignModelName);
        const auto Future = Self->Client->Issue(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FCampaignModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->CampaignModelName,
                    "IssueJob"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FIssueJobDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::SerialKey::Model::FIssueJob>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::SerialKey::Domain::Model::FIssueJobDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            Request->GetCampaignModelName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCampaignModelDomain::FIssueTask>> FCampaignModelDomain::Issue(
        Request::FIssueRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIssueTask>>(this->AsShared(), Request);
    }

    Gs2::SerialKey::Domain::Iterator::FDescribeIssueJobsIteratorPtr FCampaignModelDomain::IssueJobs(
    ) const
    {
        return MakeShared<Gs2::SerialKey::Domain::Iterator::FDescribeIssueJobsIterator>(
            Cache,
            Client,
            NamespaceName,
            CampaignModelName
        );
    }

    TSharedPtr<Gs2::SerialKey::Domain::Model::FIssueJobDomain> FCampaignModelDomain::IssueJob(
        const FString IssueJobName
    ) const
    {
        return MakeShared<Gs2::SerialKey::Domain::Model::FIssueJobDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            CampaignModelName,
            IssueJobName
        );
    }

    FString FCampaignModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> CampaignModelName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (CampaignModelName.IsSet() ? *CampaignModelName : "null") + ":" +
            ChildType;
    }

    FString FCampaignModelDomain::CreateCacheKey(
        TOptional<FString> CampaignModelName
    )
    {
        return FString() +
            (CampaignModelName.IsSet() ? *CampaignModelName : "null");
    }

    FCampaignModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FCampaignModelDomain> Self
    ): Self(Self)
    {

    }

    FCampaignModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCampaignModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::SerialKey::Model::FCampaignModel>(
            Self->ParentKey,
            Gs2::SerialKey::Domain::Model::FCampaignModelDomain::CreateCacheKey(
                Self->CampaignModelName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SerialKey::Request::FGetCampaignModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "campaignModel")
                    {
                        Self->Cache->Delete<Gs2::SerialKey::Model::FCampaignModel>(
                            Self->ParentKey,
                            Gs2::SerialKey::Domain::Model::FCampaignModelDomain::CreateCacheKey(
                                Self->CampaignModelName
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
            Value = Self->Cache->Get<Gs2::SerialKey::Model::FCampaignModel>(
                Self->ParentKey,
                Gs2::SerialKey::Domain::Model::FCampaignModelDomain::CreateCacheKey(
                    Self->CampaignModelName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCampaignModelDomain::FModelTask>> FCampaignModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCampaignModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

