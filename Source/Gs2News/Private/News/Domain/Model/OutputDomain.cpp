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

#include "News/Domain/Model/Output.h"
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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::News::Domain::Model
{

    FOutputDomain::FOutputDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UploadToken,
        const TOptional<FString> OutputName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Session)),
        NamespaceName(NamespaceName),
        UploadToken(UploadToken),
        OutputName(OutputName),
        ParentKey(Gs2::News::Domain::Model::FProgressDomain::CreateCacheParentKey(
            NamespaceName,
            UploadToken,
            "Output"
        ))
    {
    }

    FOutputDomain::FOutputDomain(
        const FOutputDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UploadToken(From.UploadToken),
        OutputName(From.OutputName),
        ParentKey(From.ParentKey)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const TSharedPtr<FOutputDomain> Self,
        const Request::FGetOutputRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FOutput>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUploadToken(Self->UploadToken)
            ->WithOutputName(Self->OutputName);
        const auto Future = Self->Client->GetOutput(
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
                const auto ParentKey = Gs2::News::Domain::Model::FProgressDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UploadToken,
                    "Output"
                );
                const auto Key = Gs2::News::Domain::Model::FOutputDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::News::Model::FOutput::TypeName,
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

    TSharedPtr<FAsyncTask<FOutputDomain::FGetTask>> FOutputDomain::Get(
        Request::FGetOutputRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FOutputDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UploadToken,
        TOptional<FString> OutputName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UploadToken.IsSet() ? *UploadToken : "null") + ":" +
            (OutputName.IsSet() ? *OutputName : "null") + ":" +
            ChildType;
    }

    FString FOutputDomain::CreateCacheKey(
        TOptional<FString> OutputName
    )
    {
        return FString("") +
            (OutputName.IsSet() ? *OutputName : "null");
    }

    FOutputDomain::FModelTask::FModelTask(
        const TSharedPtr<FOutputDomain> Self
    ): Self(Self)
    {

    }

    FOutputDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FOutput>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::News::Model::FOutput> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::News::Model::FOutput>(
            Self->ParentKey,
            Gs2::News::Domain::Model::FOutputDomain::CreateCacheKey(
                Self->OutputName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::News::Request::FGetOutputRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::News::Domain::Model::FOutputDomain::CreateCacheKey(
                    Self->OutputName
                );
                Self->Cache->Put(
                    Gs2::News::Model::FOutput::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "output")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::News::Model::FOutput>(
                Self->ParentKey,
                Gs2::News::Domain::Model::FOutputDomain::CreateCacheKey(
                    Self->OutputName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FOutputDomain::FModelTask>> FOutputDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FOutputDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FOutputDomain::Subscribe(
        TFunction<void(Gs2::News::Model::FOutputPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::News::Model::FOutput::TypeName,
            ParentKey,
            Gs2::News::Domain::Model::FOutputDomain::CreateCacheKey(
                OutputName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::News::Model::FOutput>(obj));
            }
        );
    }

    void FOutputDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::News::Model::FOutput::TypeName,
            ParentKey,
            Gs2::News::Domain::Model::FOutputDomain::CreateCacheKey(
                OutputName
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

