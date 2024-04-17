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

#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Namespace.h"
#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Output.h"
#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/User.h"
#include "News/Domain/Model/UserAccessToken.h"
#include "News/Domain/Model/News.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::News::Domain::Model
{

    FProgressDomain::FProgressDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const News::Domain::FGs2NewsDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UploadToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UploadToken(UploadToken),
        ParentKey(Gs2::News::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Progress"
        ))
    {
    }

    FProgressDomain::FProgressDomain(
        const FProgressDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UploadToken(From.UploadToken),
        ParentKey(From.ParentKey)
    {

    }

    FProgressDomain::FGetTask::FGetTask(
        const TSharedPtr<FProgressDomain>& Self,
        const Request::FGetProgressRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FProgress>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUploadToken(Self->UploadToken);
        const auto Future = Self->Client->GetProgress(
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
                const auto ParentKey = Gs2::News::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Progress"
                );
                const auto Key = Gs2::News::Domain::Model::FProgressDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUploadToken()
                );
                Self->Gs2->Cache->Put(
                    Gs2::News::Model::FProgress::TypeName,
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

    TSharedPtr<FAsyncTask<FProgressDomain::FGetTask>> FProgressDomain::Get(
        Request::FGetProgressRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::News::Domain::Iterator::FDescribeOutputsIteratorPtr FProgressDomain::Outputs(
    ) const
    {
        return MakeShared<Gs2::News::Domain::Iterator::FDescribeOutputsIterator>(
            Gs2,
            Client,
            NamespaceName,
            UploadToken
        );
    }

    Gs2::Core::Domain::CallbackID FProgressDomain::SubscribeOutputs(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::News::Model::FOutput::TypeName,
            Gs2::News::Domain::Model::FProgressDomain::CreateCacheParentKey(
                NamespaceName,
                UploadToken,
                "Output"
            ),
            Callback
        );
    }

    void FProgressDomain::UnsubscribeOutputs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::News::Model::FOutput::TypeName,
            Gs2::News::Domain::Model::FProgressDomain::CreateCacheParentKey(
                NamespaceName,
                UploadToken,
                "Output"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::News::Domain::Model::FOutputDomain> FProgressDomain::Output(
        const FString OutputName
    )
    {
        return MakeShared<Gs2::News::Domain::Model::FOutputDomain>(
            Gs2,
            Service,
            NamespaceName,
            UploadToken,
            OutputName == TEXT("") ? TOptional<FString>() : TOptional<FString>(OutputName)
        );
    }

    FString FProgressDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UploadToken,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UploadToken.IsSet() ? *UploadToken : "null") + ":" +
            ChildType;
    }

    FString FProgressDomain::CreateCacheKey(
        TOptional<FString> UploadToken
    )
    {
        return FString("") +
            (UploadToken.IsSet() ? *UploadToken : "null");
    }

    FProgressDomain::FModelTask::FModelTask(
        const TSharedPtr<FProgressDomain> Self
    ): Self(Self)
    {

    }

    FProgressDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FProgress>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::News::Model::FProgress> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::News::Model::FProgress>(
            Self->ParentKey,
            Gs2::News::Domain::Model::FProgressDomain::CreateCacheKey(
                Self->UploadToken
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::News::Request::FGetProgressRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::News::Domain::Model::FProgressDomain::CreateCacheKey(
                    Self->UploadToken
                );
                Self->Gs2->Cache->Put(
                    Gs2::News::Model::FProgress::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "progress")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::News::Model::FProgress>(
                Self->ParentKey,
                Gs2::News::Domain::Model::FProgressDomain::CreateCacheKey(
                    Self->UploadToken
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressDomain::FModelTask>> FProgressDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FProgressDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FProgressDomain::Subscribe(
        TFunction<void(Gs2::News::Model::FProgressPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::News::Model::FProgress::TypeName,
            ParentKey,
            Gs2::News::Domain::Model::FProgressDomain::CreateCacheKey(
                UploadToken
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::News::Model::FProgress>(obj));
            }
        );
    }

    void FProgressDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::News::Model::FProgress::TypeName,
            ParentKey,
            Gs2::News::Domain::Model::FProgressDomain::CreateCacheKey(
                UploadToken
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

