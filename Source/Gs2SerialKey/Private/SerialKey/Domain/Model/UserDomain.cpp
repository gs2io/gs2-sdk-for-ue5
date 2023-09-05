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

#include "SerialKey/Domain/Model/User.h"
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
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserDomain::FDownloadSerialCodesTask::FDownloadSerialCodesTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FDownloadSerialCodesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDownloadSerialCodesTask::FDownloadSerialCodesTask(
        const FDownloadSerialCodesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDownloadSerialCodesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DownloadSerialCodes(
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
        Domain->Url = Domain->Url = ResultModel->GetUrl();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FDownloadSerialCodesTask>> FUserDomain::DownloadSerialCodes(
        Request::FDownloadSerialCodesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDownloadSerialCodesTask>>(this->AsShared(), Request);
    }

    FUserDomain::FGetSerialKeyTask::FGetSerialKeyTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FGetSerialKeyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FGetSerialKeyTask::FGetSerialKeyTask(
        const FGetSerialKeyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FGetSerialKeyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FSerialKey>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetSerialKey(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "SerialKey"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FSerialKeyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCode()
                );
                Self->Cache->Put(
                    Gs2::SerialKey::Model::FSerialKey::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetCampaignModel() != nullptr)
            {
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CampaignModel"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCampaignModelDomain::CreateCacheKey(
                    ResultModel->GetCampaignModel()->GetName()
                );
                Self->Cache->Put(
                    Gs2::SerialKey::Model::FCampaignModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetCampaignModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FGetSerialKeyTask>> FUserDomain::GetSerialKey(
        Request::FGetSerialKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetSerialKeyTask>>(this->AsShared(), Request);
    }

    FUserDomain::FRevertUseTask::FRevertUseTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FRevertUseByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FRevertUseTask::FRevertUseTask(
        const FRevertUseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FRevertUseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->RevertUseByUserId(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "SerialKey"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FSerialKeyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCode()
                );
                Self->Cache->Put(
                    Gs2::SerialKey::Model::FSerialKey::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetCampaignModel() != nullptr)
            {
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CampaignModel"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCampaignModelDomain::CreateCacheKey(
                    ResultModel->GetCampaignModel()->GetName()
                );
                Self->Cache->Put(
                    Gs2::SerialKey::Model::FCampaignModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetCampaignModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetCode()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FRevertUseTask>> FUserDomain::RevertUse(
        Request::FRevertUseByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRevertUseTask>>(this->AsShared(), Request);
    }

    Gs2::SerialKey::Domain::Iterator::FDescribeSerialKeysIteratorPtr FUserDomain::SerialKeys(
        const FString CampaignModelName,
        const TOptional<FString> IssueJobName
    ) const
    {
        return MakeShared<Gs2::SerialKey::Domain::Iterator::FDescribeSerialKeysIterator>(
            Cache,
            Client,
            NamespaceName,
            CampaignModelName,
            IssueJobName
        );
    }

    TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain> FUserDomain::SerialKey(
        const FString SerialKeyCode
    ) const
    {
        return MakeShared<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            SerialKeyCode == TEXT("") ? TOptional<FString>() : TOptional<FString>(SerialKeyCode)
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

