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

#include "Experience/Domain/Model/StatusAccessToken.h"
#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/Namespace.h"
#include "Experience/Domain/Model/ExperienceModelMaster.h"
#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Domain/Model/ThresholdMaster.h"
#include "Experience/Domain/Model/CurrentExperienceMaster.h"
#include "Experience/Domain/Model/User.h"
#include "Experience/Domain/Model/UserAccessToken.h"
#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/StatusAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Experience::Domain::Model
{

    FStatusAccessTokenDomain::FStatusAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> ExperienceName,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Experience::FGs2ExperienceRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ExperienceName(ExperienceName),
        PropertyId(PropertyId),
        ParentKey(Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Status"
        ))
    {
    }

    FStatusAccessTokenDomain::FStatusAccessTokenDomain(
        const FStatusAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FStatusAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FStatusAccessTokenDomain> Self,
        const Request::FGetStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FStatus>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithExperienceName(Self->ExperienceName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetStatus(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetExperienceName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Experience::Model::FStatus>(
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FGetTask>> FStatusAccessTokenDomain::Get(
        Request::FGetStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStatusAccessTokenDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const TSharedPtr<FStatusAccessTokenDomain> Self,
        const Request::FGetStatusWithSignatureRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusAccessTokenDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const FGetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FGetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithExperienceName(Self->ExperienceName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetStatusWithSignature(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetExperienceName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Experience::Model::FStatus>(
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

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FGetWithSignatureTask>> FStatusAccessTokenDomain::GetWithSignature(
        Request::FGetStatusWithSignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetWithSignatureTask>>(this->AsShared(), Request);
    }

    FString FStatusAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> ExperienceName,
        TOptional<FString> PropertyId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (ExperienceName.IsSet() ? *ExperienceName : "null") + ":" +
            (PropertyId.IsSet() ? *PropertyId : "null") + ":" +
            ChildType;
    }

    FString FStatusAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ExperienceName,
        TOptional<FString> PropertyId
    )
    {
        return FString() +
            (ExperienceName.IsSet() ? *ExperienceName : "null") + ":" + 
            (PropertyId.IsSet() ? *PropertyId : "null");
    }

    FStatusAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FStatusAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FStatusAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FStatus>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Experience::Model::FStatus>(
            Self->ParentKey,
            Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                Self->ExperienceName,
                Self->PropertyId
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Experience::Request::FGetStatusRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "status")
                    {
                        Self->Cache->Delete<Gs2::Experience::Model::FStatus>(
                            Self->ParentKey,
                            Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                                Self->ExperienceName,
                                Self->PropertyId
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
            Value = Self->Cache->Get<Gs2::Experience::Model::FStatus>(
                Self->ParentKey,
                Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    Self->ExperienceName,
                    Self->PropertyId
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusAccessTokenDomain::FModelTask>> FStatusAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStatusAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

