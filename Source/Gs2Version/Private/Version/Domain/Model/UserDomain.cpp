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

#include "Version/Domain/Model/User.h"
#include "Version/Domain/Model/Namespace.h"
#include "Version/Domain/Model/VersionModelMaster.h"
#include "Version/Domain/Model/VersionModel.h"
#include "Version/Domain/Model/AcceptVersion.h"
#include "Version/Domain/Model/AcceptVersionAccessToken.h"
#include "Version/Domain/Model/Checker.h"
#include "Version/Domain/Model/CheckerAccessToken.h"
#include "Version/Domain/Model/User.h"
#include "Version/Domain/Model/UserAccessToken.h"
#include "Version/Domain/Model/CurrentVersionMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Version::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Version::Domain::FGs2VersionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Version::FGs2VersionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Version::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FCalculateSignatureTask::FCalculateSignatureTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FCalculateSignatureRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FCalculateSignatureTask::FCalculateSignatureTask(
        const FCalculateSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FCalculateSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CalculateSignature(
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
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetBody().IsSet())
            {
                Self->Body = Domain->Body = ResultModel->GetBody();
            }
            if (ResultModel->GetSignature().IsSet())
            {
                Self->Signature = Domain->Signature = ResultModel->GetSignature();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FCalculateSignatureTask>> FUserDomain::CalculateSignature(
        Request::FCalculateSignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCalculateSignatureTask>>(this->AsShared(), Request);
    }

    Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsByUserIdIteratorPtr FUserDomain::AcceptVersions(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeAcceptVersions(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Version::Model::FAcceptVersion::TypeName,
            Gs2::Version::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "AcceptVersion"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeAcceptVersions(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Version::Model::FAcceptVersion::TypeName,
            Gs2::Version::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "AcceptVersion"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionDomain> FUserDomain::AcceptVersion(
        const FString VersionName
    )
    {
        return MakeShared<Gs2::Version::Domain::Model::FAcceptVersionDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            VersionName == TEXT("") ? TOptional<FString>() : TOptional<FString>(VersionName)
        );
    }

    TSharedPtr<Gs2::Version::Domain::Model::FCheckerDomain> FUserDomain::Checker(
    )
    {
        return MakeShared<Gs2::Version::Domain::Model::FCheckerDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
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

