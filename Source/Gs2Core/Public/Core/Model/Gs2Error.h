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

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonValue.h"
#include "Async/AsyncWork.h"

typedef FString FGs2ErrorType;
typedef FString FGs2ErrorComponent;
typedef FString FGs2ErrorMessage;
typedef FString FGs2ErrorCode;

namespace Gs2::Core::Model
{
    class GS2CORE_API FGs2ErrorDetail
    {
        const FGs2ErrorComponent ComponentValue;
        const FGs2ErrorMessage MessageValue;
        const FGs2ErrorCode CodeValue;

    public:
        FGs2ErrorDetail(
            const FGs2ErrorComponent ComponentValue,
            const FGs2ErrorMessage MessageValue,
            const FGs2ErrorCode CodeValue
        );
        FGs2ErrorDetail(
            const FGs2ErrorDetail& From
        );
        
        ~FGs2ErrorDetail() = default;

        FGs2ErrorComponent Component() const;
        FGs2ErrorMessage Message() const;
        FGs2ErrorCode Code() const;

        FGs2ErrorComponent GetComponent() const;
        FGs2ErrorMessage GetMessage() const;
        FGs2ErrorCode GetCode() const;

        static TSharedPtr<FGs2ErrorDetail> FromJson(TSharedPtr<FJsonValue> Object);
        FString String() const;
    };
    typedef TSharedPtr<FGs2ErrorDetail, ESPMode::ThreadSafe> FGs2ErrorDetailPtr;
    
    class GS2CORE_API FGs2Error
    {
        TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details;
    public:
        explicit FGs2Error(
            const TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details
        );
        FGs2Error(
            const FGs2Error& From
        );
        virtual ~FGs2Error() = default;

        int32 Count() const
        {
            return this->Details->Num();
        }
        
        TSharedPtr<FGs2ErrorDetail> Detail(const int32 Index) const
        {
            return (*this->Details)[Index];
        }

        TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> GetErrors() const
        {
            return this->Details;
        }
        
        virtual FGs2ErrorType Type() const = 0;
        
        static TSharedPtr<FGs2Error> FromResponse(int32 StatusCode, FString Response);
        static TSharedPtr<FGs2Error> FromJson(int32 StatusCode, TArray<TSharedPtr<FJsonValue>> Objects);
        FString String() const;
    };
    typedef TSharedPtr<FGs2Error, ESPMode::ThreadSafe> FGs2ErrorPtr;

    class GS2CORE_API FBadGatewayError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "BadGateway";
        
        explicit FBadGatewayError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FBadGatewayError(
            const FBadGatewayError& From
        ): FGs2Error(From) {}
        virtual ~FBadGatewayError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FBadRequestError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "BadRequest";
        
        explicit FBadRequestError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FBadRequestError(
            const FBadRequestError& From
        ): FGs2Error(From) {}
        virtual ~FBadRequestError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FConflictError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "Conflict";
        
        explicit FConflictError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FConflictError(
            const FConflictError& From
        ): FGs2Error(From) {}
        virtual ~FConflictError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FInternalServerError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "InternalServerError";
        
        explicit FInternalServerError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FInternalServerError(
            const FInternalServerError& From
        ): FGs2Error(From) {}
        virtual ~FInternalServerError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FNotFoundError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "NotFound";
        
        explicit FNotFoundError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FNotFoundError(
            const FNotFoundError& From
        ): FGs2Error(From) {}
        virtual ~FNotFoundError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FQuotaLimitExceedError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "QuotaLimitExceed";
        
        explicit FQuotaLimitExceedError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FQuotaLimitExceedError(
            const FQuotaLimitExceedError& From
        ): FGs2Error(From) {}
        virtual ~FQuotaLimitExceedError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FServiceUnavailableError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "ServiceUnavailable";
        
        explicit FServiceUnavailableError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FServiceUnavailableError(
            const FServiceUnavailableError& From
        ): FGs2Error(From) {}
        virtual ~FServiceUnavailableError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FRequestTimeoutError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "RequestTimeout";
        
        explicit FRequestTimeoutError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FRequestTimeoutError(
            const FRequestTimeoutError& From
        ): FGs2Error(From) {}
        virtual ~FRequestTimeoutError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FUnauthorizedError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "Unauthorized";
        
        explicit FUnauthorizedError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FUnauthorizedError(
            const FUnauthorizedError& From
        ): FGs2Error(From) {}
        virtual ~FUnauthorizedError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FUnknownError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "Unknown";
        
        explicit FUnknownError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FUnknownError(
            const FUnknownError& From
        ): FGs2Error(From) {}
        virtual ~FUnknownError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FSessionNotOpenError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "SessionNotOpen";
        
        explicit FSessionNotOpenError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FSessionNotOpenError(
            const FSessionNotOpenError& From
        ): FGs2Error(From) {}
        virtual ~FSessionNotOpenError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    class GS2CORE_API FNotExecutedError : public FGs2Error
    {
    public:
        inline static const FGs2ErrorType TypeString = "Gs2NotExecuted";
        
        explicit FNotExecutedError(TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details): FGs2Error(Details) {}
        FNotExecutedError(
            const FNotExecutedError& From
        ): FGs2Error(From) {}
        virtual ~FNotExecutedError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }
    };
    
    template<class TTask>
    class FTransactionError final : public FGs2Error
    {
        TFunction<TSharedPtr<FAsyncTask<TTask>> ()> RetryFunction;
    public:
        inline static const FGs2ErrorType TypeString = "Transaction";
        
        FTransactionError(
            const TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details,
            const TFunction<TSharedPtr<FAsyncTask<TTask>> ()> Retry
        ): FGs2Error(Details), RetryFunction(Retry) {}
        FTransactionError(
            const FTransactionError& From
        ): FGs2Error(From), RetryFunction(From.RetryFunction) {}
        virtual ~FTransactionError() override = default;
        
        virtual FGs2ErrorType Type() const override
        {
            return TypeString;
        }

        TSharedPtr<FAsyncTask<TTask>> Retry() const
        {
            return RetryFunction();
        }
    };
}
